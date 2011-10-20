/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2009-2011 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    rhoCentralFoam

Description
    Density-based compressible flow solver based on central-upwind schemes of
    Kurganov and Tadmor

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "basicPsiThermo.H"
#include "turbulenceModel.H"
#include "zeroGradientFvPatchFields.H"
#include "fixedRhoFvPatchScalarField.H"

#include "core.hpp"
#include "basicPsiThermoHolder.hpp"
#include "turbulenceModels/compressible/turbulenceModel/turbulenceModelHolder.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
wordList fun_rhoBoundaryTypes( const volScalarFieldHolder& p )
{
  const volScalarField::GeometricBoundaryField& pbf = p->boundaryField();
  wordList rhoBoundaryTypes = pbf.types();

  forAll(rhoBoundaryTypes, patchi)
  {
    if (rhoBoundaryTypes[patchi] == "waveTransmissive")
    {
      rhoBoundaryTypes[patchi] = zeroGradientFvPatchScalarField::typeName;
    }
    else if (pbf[patchi].fixesValue())
    {
      rhoBoundaryTypes[patchi] = fixedRhoFvPatchScalarField::typeName;
    }
  }
  
  return rhoBoundaryTypes;
}


//---------------------------------------------------------------------------
bool createFields( const TimeHolder& runTime, const fvMeshHolder& mesh,
                   basicPsiThermoHolder& pThermo, volScalarFieldHolder& rho,
                   volScalarFieldHolder& p, volScalarFieldHolder& e,
                   volScalarFieldHolder& T, volScalarFieldHolder& psi, 
                   volScalarFieldHolder& mu, volVectorFieldHolder& U, 
                   volVectorFieldHolder& rhoU, volScalarFieldHolder& rhoE,
                   surfaceScalarFieldHolder& pos, surfaceScalarFieldHolder& neg, 
                   surfaceScalarFieldHolder& phi, compressible::turbulenceModelHolder& turbulence )
{
  Info<< "Reading thermophysical properties\n" << endl;
  pThermo = basicPsiThermoHolder::New( mesh );
  
  p( volScalarFieldHolder( pThermo->p(), Deps( &pThermo ) ) );
  e( volScalarFieldHolder( pThermo->e(), Deps( &pThermo ) ) );
  T( volScalarFieldHolder( pThermo->T(), Deps( &pThermo ) ) );
  psi( volScalarFieldHolder( pThermo->psi(), Deps( &pThermo ) ) );
  mu( volScalarFieldHolder( pThermo->mu(), Deps( &pThermo ) ) );
  
  bool inviscid(true);
  if ( max( mu->internalField() ) > 0.0 )
  {
    inviscid = false;
  }

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  wordList rhoBoundaryTypes = fun_rhoBoundaryTypes( p );
  
  rho( volScalarFieldHolder( IOobjectHolder( "rho",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::NO_READ,
                                             IOobject::AUTO_WRITE ),
                             volScalarFieldHolder( pThermo->rho(), Deps( & pThermo ) ),
                             rhoBoundaryTypes ) );

  rhoU( volVectorFieldHolder( IOobjectHolder( "rhoU",
                                               runTime->timeName(),
                                               mesh,
                                               IOobject::NO_READ,
                                               IOobject::NO_WRITE ),
                               rho * U ) );

  rhoE( volScalarFieldHolder( IOobjectHolder( "rhoE",
                                              runTime->timeName(),
                                              mesh,
                                              IOobject::NO_READ,
                                              IOobject::NO_WRITE ),
                              rho * ( e + 0.5 * volScalarFieldHolder( magSqr( U() ), Deps( &U ) ) ) ) );

  pos( surfaceScalarFieldHolder( IOobjectHolder( "pos",
                                                 runTime->timeName(),
                                                 mesh ),
                                 mesh,
                                 dimensionedScalar( "pos", dimless, 1.0 ) ) );

  neg( surfaceScalarFieldHolder( IOobjectHolder( "neg",
                                                 runTime->timeName(),
                                                 mesh ),
                                 mesh,
                                 dimensionedScalar("neg", dimless, -1.0) ) );
  
  phi( surfaceScalarFieldHolder( "phi", surfaceVectorFieldHolder( mesh->Sf(), Deps( &mesh ) ) & fvc::interpolate( rhoU ) ) );
  
  Info<< "Creating turbulence model\n" << endl;
  turbulence = compressible::turbulenceModelHolder::New( rho, U, phi, pThermo );
  
  return inviscid;
}


//---------------------------------------------------------------------------
dimensionedScalar readThermophysicalProperties( const TimeHolder& runTime, const fvMeshHolder& mesh, 
                                                IOdictionaryHolder& thermophysicalProperties )
{
  Info<< "Reading thermophysicalProperties\n" << endl;

  // Pr defined as a separate constant to enable calculation of k, currently
  // inaccessible through thermo
  thermophysicalProperties = IOdictionaryHolder( IOobjectHolder( "thermophysicalProperties",
                                                                 runTime->constant(),
                                                                 mesh,
                                                                 IOobject::MUST_READ_IF_MODIFIED,
                                                                 IOobject::NO_WRITE ) );

  dimensionedScalar Pr( dimensionedScalar::lookupOrDefault( "Pr",
                                                            *thermophysicalProperties,
                                                            1.0 ) );
  
  return Pr;
}


//---------------------------------------------------------------------------
word readFluxScheme( const fvMeshHolder& mesh )
{
  word fluxScheme("Kurganov");
  if ( mesh->schemesDict().readIfPresent( "fluxScheme", fluxScheme ) )
  {
    if ( ( fluxScheme == "Tadmor" ) || ( fluxScheme == "Kurganov" ) )
    {
      Info<< "fluxScheme: " << fluxScheme << endl;
    }
    else
    {
      FatalErrorIn
      (
          "rhoCentralFoam::readFluxScheme"
      )   << "fluxScheme: " << fluxScheme
          << " is not a valid choice. "
          << "Options are: Tadmor, Kurganov"
          << abort(FatalError);
    }
  }
  
  return fluxScheme;
}


//---------------------------------------------------------------------------
void compressibleCourantNo( const TimeHolder& runTime,  const fvMeshHolder& mesh, 
                            const surfaceScalarField& amaxSf, scalar& CoNum, scalar& meanCoNum )
{
  CoNum = 0.0;
  meanCoNum = 0.0;

  if (mesh->nInternalFaces())
  {
    smart_tmp< surfaceScalarField > amaxSfbyDelta( mesh->surfaceInterpolation::deltaCoeffs() * amaxSf );

    CoNum = max( amaxSfbyDelta() / mesh->magSf() ).value() * runTime->deltaTValue();

    meanCoNum = ( sum( amaxSfbyDelta() ) / sum( mesh->magSf() ) ).value() * runTime->deltaTValue();
  }

  Info<< "Mean and max Courant Numbers = "
      << meanCoNum << " " << CoNum << endl;
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  basicPsiThermoHolder pThermo; volScalarFieldHolder rho;
  volScalarFieldHolder p; volScalarFieldHolder e;
  volScalarFieldHolder T; volScalarFieldHolder psi;
  volScalarFieldHolder mu; volVectorFieldHolder U;
  volVectorFieldHolder rhoU; volScalarFieldHolder rhoE;
  surfaceScalarFieldHolder pos; surfaceScalarFieldHolder neg;
  surfaceScalarFieldHolder phi; compressible::turbulenceModelHolder turbulence;
  
  bool inviscid = createFields( runTime, mesh, pThermo, rho, p, e, T, psi, mu, U, rhoU, rhoE, pos, neg, phi, turbulence );
  
  IOdictionaryHolder thermophysicalProperties;
  
  dimensionedScalar Pr = readThermophysicalProperties( runTime, mesh, thermophysicalProperties );
  
  bool adjustTimeStep; scalar maxCo; scalar maxDeltaT;
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
  
  word fluxScheme = readFluxScheme( mesh );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
  dimensionedScalar v_zero("v_zero", dimVolume/dimTime, 0.0);
 
  Info<< "\nStarting time loop\n" << endl;

  while (runTime->run())
  {
    // --- upwind interpolation of primitive fields on faces

    smart_tmp< surfaceScalarField > rho_pos( fvc::interpolate( rho(), pos(), "reconstruct(rho)" ) );
    smart_tmp< surfaceScalarField > rho_neg( fvc::interpolate( rho(), neg(), "reconstruct(rho)" ) );
    smart_tmp< surfaceVectorField > rhoU_pos( fvc::interpolate( rhoU(), pos(), "reconstruct(U)" ) );
    smart_tmp< surfaceVectorField > rhoU_neg( fvc::interpolate( rhoU(), neg(), "reconstruct(U)" ) );
    smart_tmp< volScalarField > rPsi( 1.0 / psi );
    smart_tmp< surfaceScalarField > rPsi_pos( fvc::interpolate( rPsi(), pos(), "reconstruct(T)" ) );
    smart_tmp< surfaceScalarField > rPsi_neg( fvc::interpolate( rPsi(), neg(), "reconstruct(T)" ) );
    smart_tmp< surfaceScalarField > e_pos( fvc::interpolate( e(), pos(), "reconstruct(T)" ) );
    smart_tmp< surfaceScalarField > e_neg( fvc::interpolate( e(), neg(), "reconstruct(T)" ) );
    smart_tmp< surfaceVectorField > U_pos( rhoU_pos() / rho_pos() );
    smart_tmp< surfaceVectorField > U_neg( rhoU_neg() / rho_neg() );
    smart_tmp< surfaceScalarField > p_pos( rho_pos() * rPsi_pos() );
    smart_tmp< surfaceScalarField > p_neg( rho_neg() * rPsi_neg() );
    smart_tmp< surfaceScalarField > phiv_pos( U_pos() & mesh->Sf());
    smart_tmp< surfaceScalarField > phiv_neg( U_neg() & mesh->Sf());
    smart_tmp< volScalarField > c( sqrt( pThermo->Cp() / pThermo->Cv() * rPsi() ) );
    smart_tmp< surfaceScalarField > cSf_pos( fvc::interpolate( c(), pos(), "reconstruct(T)" ) * mesh->magSf() );
    smart_tmp< surfaceScalarField > cSf_neg( fvc::interpolate( c() , neg(), "reconstruct(T)" ) * mesh->magSf() );
    smart_tmp< surfaceScalarField > ap( max( max( phiv_pos() + cSf_pos(), phiv_neg() + cSf_neg() ), v_zero ) );
    smart_tmp< surfaceScalarField > am( min( min( phiv_pos() - cSf_pos(), phiv_neg() - cSf_neg() ), v_zero ) );
    smart_tmp< surfaceScalarField > a_pos( ap() / ( ap() - am() ) );
    
    surfaceScalarField amaxSf( "amaxSf", max( mag( am() ), mag( ap() ) ) );
    smart_tmp< surfaceScalarField > aSf( am() * a_pos() );

    if (fluxScheme == "Tadmor")
    {
      aSf = -0.5 * amaxSf;
      a_pos() = 0.5;
    }

    smart_tmp< surfaceScalarField > a_neg( 1.0 - a_pos() );

    phiv_pos() *= a_pos();
    phiv_neg() *= a_neg();

    smart_tmp< surfaceScalarField > aphiv_pos( phiv_pos() - aSf() );
    smart_tmp< surfaceScalarField > aphiv_neg( phiv_neg() + aSf() );

    // Reuse amaxSf for the maximum positive and negative fluxes
    // estimated by the central scheme
    amaxSf = max( mag( aphiv_pos() ), mag( aphiv_neg() ));

    scalar coNum, meanCoNum;
    compressibleCourantNo( runTime, mesh, amaxSf, coNum, meanCoNum );
    readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
    setDeltaT( runTime, adjustTimeStep, maxCo, coNum, maxDeltaT );
    
    ( *runTime )++;

    Info<< "Time = " << runTime->timeName() << nl << endl;

    surfaceScalarField phi( "phi", aphiv_pos() * rho_pos() + aphiv_neg() * rho_neg() );
    
    smart_tmp< surfaceVectorField > phiUp( ( aphiv_pos() * rhoU_pos() + aphiv_neg() * rhoU_neg() ) + 
                                           ( a_pos() * p_pos() + a_neg() * p_neg() ) * mesh->Sf() );

    smart_tmp< surfaceScalarField > phiEp( aphiv_pos() * ( rho_pos() * ( e_pos() + 0.5 * magSqr( U_pos() ) ) + p_pos() )
                                                         + aphiv_neg() * ( rho_neg() * ( e_neg() + 0.5 * magSqr( U_neg() ) ) + p_neg() )
                                                         + aSf() * p_pos() - aSf() *p_neg() );

    smart_tmp< volScalarField > muEff( turbulence->muEff() );
    volTensorField tauMC( "tauMC", muEff() * dev2( Foam::T( fvc::grad( U() ) ) ) );

    // --- Solve density
    solve( fvm::ddt( rho() ) + fvc::div( phi ) );

    // --- Solve momentum
    solve( fvm::ddt( rhoU() ) + fvc::div( phiUp() ) );

    U->dimensionedInternalField() = rhoU->dimensionedInternalField() / rho->dimensionedInternalField();
    U->correctBoundaryConditions();
    rhoU->boundaryField() = rho->boundaryField() * U->boundaryField();

    smart_tmp< volScalarField > rhoBydt( rho() / runTime->deltaT() );

    if ( !inviscid )
    {
      solve( fvm::ddt( rho() , U() ) - fvc::ddt( rho(), U() ) - fvm::laplacian( muEff(), U() ) - fvc::div( tauMC ) );
      rhoU = rho * U;
    }

    // --- Solve energy
    smart_tmp< surfaceScalarField > sigmaDotU( ( fvc::interpolate( muEff() ) * mesh->magSf() * fvc::snGrad( U() ) 
                                                 + ( mesh->Sf() & fvc::interpolate( tauMC ) ) ) & ( a_pos() * U_pos() + a_neg() * U_neg() ) );

    solve( fvm::ddt( rhoE() ) + fvc::div( phiEp() ) - fvc::div( sigmaDotU() ) );
    
    e = rhoE() / rho() - 0.5 * magSqr( U() );
    e->correctBoundaryConditions();
    
    pThermo->correct();
    
    rhoE->boundaryField() = rho->boundaryField() * ( e->boundaryField() + 0.5 * magSqr( U->boundaryField() ) );

    if ( !inviscid )
    {
      volScalarField k( "k", pThermo->Cp() * muEff() / Pr );
      solve( fvm::ddt( rho(), e() ) - fvc::ddt( rho(), e() ) - fvm::laplacian( turbulence->alphaEff(), e() )
             + fvc::laplacian(turbulence->alpha(), e() ) - fvc::laplacian( k, T() ) );
      pThermo->correct();
      
      rhoE = rho() * ( e() + 0.5 * magSqr( U() ) );
    }

    p->dimensionedInternalField() = rho->dimensionedInternalField() / psi->dimensionedInternalField();
    p->correctBoundaryConditions();
    rho->boundaryField() = psi->boundaryField() * p->boundaryField();

    turbulence->correct();

    runTime->write();

    Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime->elapsedClockTime() << " s"
        << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}

// ************************************************************************* //
