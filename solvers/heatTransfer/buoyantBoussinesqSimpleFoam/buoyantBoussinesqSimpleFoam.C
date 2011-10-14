/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2008-2011 OpenCFD Ltd.
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
    buoyantBoussinesqSimpleFoam

Description
    Steady-state solver for buoyant, turbulent flow of incompressible fluids

    Uses the Boussinesq approximation:
    \f[
        rho_{eff} = 1 - beta(T - T_{ref})
    \f]

    where:
        \f$ rho_{eff} \f$ = the effective (driving) density
        beta = thermal expansion coefficient [1/K]
        T = temperature [K]
        \f$ T_{ref} \f$ = reference temperature [K]

    Valid when:
    \f[
        rho_{eff} << 1
    \f]

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"

#include "singlePhaseTransportModelHolder.hpp"
#include "turbulenceModels/incompressible/RAS/RASModelHolder.hpp"
#include "simpleControlHolder.hpp"


//---------------------------------------------------------------------------
struct result_readTransportProperties
{
  dimensionedScalar m_beta;
  dimensionedScalar m_TRef;
  dimensionedScalar m_Pr;
  dimensionedScalar m_Prt;
  result_readTransportProperties( dimensionedScalar the_beta, dimensionedScalar the_TRef, dimensionedScalar the_Pr, dimensionedScalar the_Prt )
    : m_beta( the_beta )
    , m_TRef( the_TRef )
    , m_Pr( the_Pr )
    , m_Prt( the_Prt )
  {}
};


//---------------------------------------------------------------------------
result_readTransportProperties readTransportProperties( const volVectorFieldHolder& U, 
                                                        const surfaceScalarFieldHolder& phi,
                                                        singlePhaseTransportModelHolder& laminarTransport )
{
  laminarTransport = singlePhaseTransportModelHolder( U, phi );

  // Thermal expansion coefficient [1/K]
  dimensionedScalar beta(laminarTransport->lookup("beta"));

  // Reference temperature [K]
  dimensionedScalar TRef(laminarTransport->lookup("TRef"));

  // Laminar Prandtl number
  dimensionedScalar Pr(laminarTransport->lookup("Pr"));

  // Turbulent Prandtl number
  dimensionedScalar Prt(laminarTransport->lookup("Prt"));
  
  return result_readTransportProperties( beta, TRef, Pr, Prt );
}


//---------------------------------------------------------------------------
result_readTransportProperties createFields( const TimeHolder& runTime, 
                                             const fvMeshHolder& mesh,
                                             const uniformDimensionedVectorField& g,
                                             volScalarFieldHolder& T,
                                             volScalarFieldHolder& p_rgh,
                                             volVectorFieldHolder& U,
                                             surfaceScalarFieldHolder& phi,
                                             singlePhaseTransportModelHolder& laminarTransport,
                                             incompressible::RASModelHolder& turbulence,
                                             volScalarFieldHolder& rhok,
                                             volScalarFieldHolder& kappat,
                                             volScalarFieldHolder& gh,
                                             surfaceScalarFieldHolder& ghf,
                                             volScalarFieldHolder& p,
                                             label& pRefCell,
                                             scalar& pRefValue )
{
  Info<< "Reading thermophysical properties\n" << endl;
  
  Info<< "Reading field T\n" << endl;
  T( volScalarFieldHolder( IOobjectHolder( "T",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ),
                            mesh ) );

  Info<< "Reading field p_rgh\n" << endl;
  p_rgh( volScalarFieldHolder( IOobjectHolder( "p_rgh",
                                                runTime->timeName(),
                                                mesh,
                                                IOobject::MUST_READ,
                                                IOobject::AUTO_WRITE ),
                                mesh ) );
  
  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ),
                            mesh ) );

  phi( createPhi( runTime, mesh, U ) );
    
  result_readTransportProperties result_readTransProp( readTransportProperties( U, phi, laminarTransport ) );
  
  dimensionedScalar beta = result_readTransProp.m_beta;
  dimensionedScalar TRef = result_readTransProp.m_TRef;
  
  Info<< "Creating turbulence model\n" << endl;
  turbulence = incompressible::RASModelHolder::New(U, phi, laminarTransport); 

  // Kinematic density for buoyancy force
  rhok( volScalarFieldHolder( IOobjectHolder( "rhok",
                                               runTime->timeName(),
                                               mesh ),
                               volScalarFieldHolder( 1.0 - beta * ( T() - TRef ), &T ) ) );
  
  // kinematic turbulent thermal thermal conductivity m2/s
  Info<< "Reading field kappat\n" << endl;
  kappat( volScalarFieldHolder( IOobjectHolder( "kappat",
                                                 runTime->timeName(),
                                                 mesh,
                                                 IOobject::MUST_READ,
                                                 IOobject::AUTO_WRITE ),
                                   mesh ) );

  Info<< "Calculating field g.h\n" << endl;
  gh( volScalarFieldHolder("gh", volScalarFieldHolder( g & mesh->C(), &mesh ) ) );
  ghf(  surfaceScalarFieldHolder("ghf", surfaceScalarFieldHolder( g & mesh->Cf(), &mesh ) ) );

  p( volScalarFieldHolder( IOobjectHolder( "p",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::NO_READ,
                                            IOobject::AUTO_WRITE ),
                            p_rgh + rhok*gh ) );

  setRefCell( p, p_rgh, mesh->solutionDict().subDict("SIMPLE"), pRefCell, pRefValue );

  if ( p_rgh->needReference() )
  {
    p += dimensionedScalar( "p",
                            p->dimensions(),
                            pRefValue - getRefCellValue( p, pRefCell ) );
  }
  
  return result_readTransProp;
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_UEqn( const fvMeshHolder& mesh,
                               const simpleControlHolder& simple,
                               volVectorFieldHolder& U, 
                               const surfaceScalarFieldHolder& phi, 
                               const incompressible::RASModelHolder& turbulence,
                               const volScalarFieldHolder& p,
                               const volScalarFieldHolder& rhok,
                               const volScalarFieldHolder& p_rgh,
                               const surfaceScalarFieldHolder& ghf )
{
  fvVectorMatrixHolder UEqn = fvm::div(phi, U) + fvVectorMatrixHolder( turbulence->divDevReff( U() ), Deps( &turbulence, &U ) ) ;

  UEqn().relax();

  if ( simple->momentumPredictor() )
  {
    solve( UEqn == fvc::reconstruct( ( - ghf*fvc::snGrad( rhok ) - fvc::snGrad( p_rgh ) ) * surfaceScalarFieldHolder( mesh->magSf(), &mesh ) ) );
  }
  return UEqn;
}


//---------------------------------------------------------------------------
void fun_TEqn( const surfaceScalarFieldHolder& phi, 
               incompressible::RASModelHolder& turbulence,
               volScalarFieldHolder& kappat,
               const volScalarFieldHolder& T,
               volScalarFieldHolder& rhok,
               const dimensionedScalar& beta,
               const dimensionedScalar& TRef,
               const dimensionedScalar& Prt,
               const dimensionedScalar Pr )
{
  kappat = turbulence->nut() / Prt;
  
  kappat->correctBoundaryConditions();
  
  volScalarField kappaEff("kappaEff", turbulence->nu()/Pr  + kappat() );

  smart_tmp< fvScalarMatrix > TEqn( fvm::div( phi(), T() ) - fvm::Sp(fvc::div( phi() ), T() ) - fvm::laplacian( kappaEff, T() ) );

  TEqn->relax();
  TEqn->solve();

  rhok = 1.0 - beta * ( T() - TRef );
}


//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               const simpleControlHolder& simple,
               volScalarFieldHolder& p,
               volScalarFieldHolder& rhok,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& phi,
               incompressible::RASModelHolder& turbulence,
               volScalarFieldHolder& gh,
               surfaceScalarFieldHolder& ghf,
               volScalarFieldHolder& p_rgh,
               fvVectorMatrixHolder& UEqn,
               label& pRefCell,
               scalar& pRefValue,
               scalar& cumulativeContErr )
{
  volScalarField rAU("rAU", 1.0/UEqn->A());
  
  surfaceScalarField rAUf("(1|A(U))", fvc::interpolate( rAU ) );

  U = rAU * UEqn->H();

  phi = fvc::interpolate( U() ) & mesh->Sf();
  adjustPhi(phi, U, p_rgh);

  smart_tmp< surfaceScalarField > buoyancyPhi( rAUf * ghf() * fvc::snGrad( rhok() ) * mesh->magSf() );
  phi -= buoyancyPhi();

  for (int nonOrth=0; nonOrth<=simple->nNonOrthCorr(); nonOrth++)
  {
    smart_tmp< fvScalarMatrix > p_rghEqn = fvm::laplacian( rAUf, p_rgh() ) == fvc::div( phi() );

    p_rghEqn->setReference( pRefCell, getRefCellValue( p_rgh, pRefCell ) );
    
    p_rghEqn->solve();

    if ( nonOrth == simple->nNonOrthCorr() )
    {
      // Calculate the conservative fluxes
      phi -= p_rghEqn->flux();

      // Explicitly relax pressure for momentum corrector
      p_rgh->relax();

      // Correct the momentum source with the pressure gradient flux
      // calculated from the relaxed pressure
      U -= rAU * fvc::reconstruct( ( buoyancyPhi() + p_rghEqn->flux() ) / rAUf );
      U->correctBoundaryConditions();
    }
  }

  continuityErrors( runTime, mesh, phi, cumulativeContErr );

  p = p_rgh + rhok * gh;

  if ( p_rgh->needReference() )
  {
    p += dimensionedScalar( "p", p->dimensions(), pRefValue - getRefCellValue( p(), pRefCell ) );

    p_rgh = p - rhok * gh;
  }

}

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  uniformDimensionedVectorField g = readGravitationalAcceleration( runTime, mesh );

  volScalarFieldHolder T; volScalarFieldHolder p_rgh;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  singlePhaseTransportModelHolder laminarTransport;
  incompressible::RASModelHolder turbulence;
  volScalarFieldHolder rhok; volScalarFieldHolder kappat;
  volScalarFieldHolder gh; surfaceScalarFieldHolder ghf;
  volScalarFieldHolder p; 
  label pRefCell = 0; 
  scalar pRefValue = 0.0;
  
  result_readTransportProperties result = createFields( runTime, mesh, g, T, p_rgh, U, phi, laminarTransport, turbulence, rhok,
                                                        kappat, gh, ghf, p, pRefCell, pRefValue );
                                                        
  dimensionedScalar& beta = result.m_beta;
  dimensionedScalar& TRef = result.m_TRef;
  dimensionedScalar& Pr = result.m_Pr;
  dimensionedScalar& Prt = result.m_Prt;
  
  scalar cumulativeContErr = initContinuityErrs();

  simpleControlHolder simple(mesh);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;

  while (simple->loop())
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;

    p_rgh->storePrevIter();

    // Pressure-velocity SIMPLE corrector
    {
      fvVectorMatrixHolder UEqn = fun_UEqn( mesh, simple, U, phi, turbulence, p, rhok, p_rgh, ghf );
      fun_TEqn( phi, turbulence, kappat, T, rhok, beta, TRef, Prt, Pr );

      fun_pEqn( mesh, runTime, simple, p, rhok, U, phi, turbulence, gh, ghf, p_rgh, UEqn, pRefCell, pRefValue, cumulativeContErr );
    }


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
