/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2011 OpenCFD Ltd.
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
    compressibleInterFoam

Description
    Solver for 2 compressible, isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

    Turbulence modelling is generic, i.e.  laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "MULES.H"
#include "subCycle.H"
#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "interfacePropertiesHolder.hpp"
#include "twoPhaseMixtureHolder.hpp"
#include "turbulenceModelHolder.hpp"
#include "pimpleControlHolder.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
void readControls( const TimeHolder& runTime, const pimpleControlHolder& pimple, const argList& args,
                   bool& adjustTimeStep, scalar& maxCo, scalar& maxDeltaT, label& nAlphaCorr, label& nAlphaSubCycles )
{
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );

  nAlphaCorr = readLabel( pimple->dict().lookup( "nAlphaCorr" ) );
  nAlphaSubCycles = readLabel( pimple->dict().lookup( "nAlphaSubCycles" ) );
  
  if (nAlphaSubCycles > 1 && pimple->nOuterCorr() != 1)
  {
    FatalErrorIn(args.executable()) << "Sub-cycling alpha is only allowed for PISO, " 
                                       "i.e. when the number of outer-correctors = 1"
                                    << exit(FatalError);
  }
}


//---------------------------------------------------------------------------
struct result_createFields
{
  dimensionedScalar m_rho10;
  dimensionedScalar m_rho20;
  dimensionedScalar m_psi1;
  dimensionedScalar m_psi2;
  dimensionedScalar m_pMin;
  result_createFields( dimensionedScalar the_rho10, dimensionedScalar the_rho20,
                       dimensionedScalar the_psi1, dimensionedScalar the_psi2,
                       dimensionedScalar the_pMin )
    : m_rho10( the_rho10 )
    , m_rho20( the_rho20 )
    , m_psi1( the_psi1 )
    , m_psi2( the_psi2 )
    , m_pMin( the_pMin )
  {}
};

result_createFields createFields( const TimeHolder& runTime, const fvMeshHolder& mesh, 
                                  const uniformDimensionedVectorFieldHolder& g,
                                  volScalarFieldHolder& p_rgh,
                                  volScalarFieldHolder& alpha1,
                                  volScalarFieldHolder& alpha2,
                                  volVectorFieldHolder& U,
                                  surfaceScalarFieldHolder& phi,
                                  twoPhaseMixtureHolder& twoPhaseProperties,
                                  volScalarFieldHolder& gh,
                                  surfaceScalarFieldHolder& ghf,
                                  volScalarFieldHolder& p,
                                  volScalarFieldHolder& rho1,
                                  volScalarFieldHolder& rho2,
                                  volScalarFieldHolder& rho,
                                  surfaceScalarFieldHolder& rhoPhi,
                                  volScalarFieldHolder& dgdt,
                                  interfacePropertiesHolder& interface,
                                  incompressible::turbulenceModelHolder& turbulence )
{
  Info<< "Reading field p_rgh\n" << endl;
  p_rgh( volScalarFieldHolder( IOobjectHolder( "p_rgh",
                                               runTime->timeName(),
                                               mesh,
                                               IOobject::MUST_READ,
                                               IOobject::AUTO_WRITE ),
                               mesh ) );

  Info<< "Reading field alpha1\n" << endl;
  alpha1( volScalarFieldHolder( IOobjectHolder( "alpha1",
                                                runTime->timeName(),
                                                mesh,
                                                IOobject::MUST_READ,
                                                IOobject::AUTO_WRITE ),
                                mesh ) );

  Info<< "Calculating field alpha1\n" << endl;
  alpha2( volScalarFieldHolder( "alpha2", scalar( 1 ) - alpha1 ) );

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  phi( createPhi( runTime, mesh, U ) );


  Info<< "Reading transportProperties\n" << endl;
  twoPhaseProperties( twoPhaseMixtureHolder(U, phi) );

  dimensionedScalar rho10( twoPhaseProperties->subDict( twoPhaseProperties->phase1Name() ).lookup( "rho0" ) );
  dimensionedScalar rho20( twoPhaseProperties->subDict( twoPhaseProperties->phase2Name() ).lookup( "rho0" ) );
  dimensionedScalar psi1( twoPhaseProperties->subDict( twoPhaseProperties->phase1Name() ).lookup( "psi" ) );
  dimensionedScalar psi2( twoPhaseProperties->subDict( twoPhaseProperties->phase2Name() ).lookup( "psi" ) );
  dimensionedScalar pMin(twoPhaseProperties->lookup("pMin"));

  Info<< "Calculating field g.h\n" << endl;
  gh( volScalarFieldHolder("gh", g & volVectorFieldHolder( mesh->C(), Deps( &mesh ) ) ) );
  ghf( surfaceScalarFieldHolder( "ghf", g & surfaceVectorFieldHolder( mesh->Cf(), Deps( &mesh ) ) ) );

  p( volScalarFieldHolder( IOobjectHolder( "p",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::NO_READ,
                                           IOobject::AUTO_WRITE ),
                           max( ( p_rgh + gh * ( alpha1 * rho10 + alpha2 * rho20) ) / 
                                ( 1.0 - gh * ( alpha1 * psi1 + alpha2 * psi2)),
                                pMin ) ) );

  rho1( volScalarFieldHolder( rho10 + psi1 * p ) );
  rho2( volScalarFieldHolder( rho20 + psi2 * p ) );

  rho( volScalarFieldHolder( IOobjectHolder( "rho",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::READ_IF_PRESENT,
                                             IOobject::AUTO_WRITE ),
                             alpha1 * rho1 + alpha2 * rho2 ) );

  // Mass flux
  // Initialisation does not matter because rhoPhi is reset after the
  // alpha1 solution before it is used in the U equation.
  rhoPhi( surfaceScalarFieldHolder( IOobjectHolder( "rho*phi",
                                                    runTime->timeName(),
                                                    mesh,
                                                    IOobject::NO_READ,
                                                    IOobject::NO_WRITE ),
                                    fvc::interpolate( rho ) * phi ) );

  dgdt( volScalarFieldHolder( pos( alpha2 ) * fvc::div( phi )/ max( alpha2, scalar( 0.0001 ) ) ) );

  // Construct interface from alpha1 distribution
  interface( interfacePropertiesHolder( alpha1, U, twoPhaseProperties ) );

  // Construct incompressible turbulence model
  turbulence( incompressible::turbulenceModelHolder::New( U, phi, twoPhaseProperties ) );
  
  return result_createFields( rho10, rho20, psi1, psi2, pMin );
}


//---------------------------------------------------------------------------
void alphaEqns( const TimeHolder& runTime, const fvMeshHolder& mesh,
                interfacePropertiesHolder& interface,
                volScalarFieldHolder& dgdt,
                volScalarFieldHolder& alpha1,
                volScalarFieldHolder& alpha2,
                smart_tmp< volScalarField >& divU,
                smart_tmp< surfaceScalarField > phic,
                surfaceScalarFieldHolder& phi,
                surfaceScalarFieldHolder& rhoPhi,
                volScalarFieldHolder& rho1,
                volScalarFieldHolder& rho2,
                label& nAlphaCorr )
                
{
  word alphaScheme("div(phi,alpha)");
  word alpharScheme("div(phirb,alpha)");

  smart_tmp< surfaceScalarField > phir( phic() * interface->nHatf() );

  for ( int gCorr=0; gCorr<nAlphaCorr; gCorr++ )
  {
    volScalarField::DimensionedInternalField Sp( IOobject( "Sp",
                                                           runTime->timeName(),
                                                           *mesh ),
                                                 *mesh,
                                                 dimensionedScalar( "Sp", dgdt->dimensions(), 0.0 ) );
    volScalarField::DimensionedInternalField Su( IOobject( "Su",
                                                           runTime->timeName(),
                                                           *mesh ),
                                                 // Divergence term is handled explicitly to be
                                                 // consistent with the explicit transport solution
                                                 divU() * min( alpha1(), scalar(1) ) );
    forAll(dgdt(), celli)
    {
      if ( dgdt()[ celli ] > 0.0 && alpha1()[ celli ] > 0.0 )
      {
        Sp[ celli ] -= dgdt()[ celli ] * alpha1()[ celli ];
        Su[celli] +=  dgdt()[ celli ] * alpha1()[ celli ];
      }
      else if ( dgdt()[ celli ] < 0.0 && alpha1()[ celli ] < 1.0 )
      {
        Sp[ celli ] += dgdt()[ celli ] * ( 1.0 - alpha1()[ celli ] );
      }
    }
    smart_tmp< surfaceScalarField > phiAlpha1( fvc::flux( phi(), alpha1(), alphaScheme ) + 
                                               fvc::flux( -fvc::flux( -phir(), alpha2(), alpharScheme ), alpha1(), alpharScheme ) );

    MULES::explicitSolve( geometricOneField(), alpha1(), phi(), phiAlpha1(), Sp, Su, 1, 0 );

    smart_tmp< surfaceScalarField > rho1f( fvc::interpolate( rho1() ) );
    smart_tmp< surfaceScalarField > rho2f( fvc::interpolate( rho2() ) );
    
    rhoPhi = phiAlpha1() * ( rho1f() - rho2f() ) + phi() * rho2f();

    alpha2 = scalar(1) - alpha1();
  }

  Info<< "Liquid phase volume fraction = "
      << alpha1->weightedAverage(mesh->V()).value()
      << "  Min(alpha1) = " << min( alpha1() ).value()
      << "  Min(alpha2) = " << min( alpha2() ).value()
      << endl;
}


//---------------------------------------------------------------------------
void alphaEqnsSubCycle( const TimeHolder& runTime, const fvMeshHolder& mesh,
                       pimpleControlHolder& pimple,
                       volScalarFieldHolder& alpha1,
                       volScalarFieldHolder& alpha2,
                       volScalarFieldHolder& rho,
                       volScalarFieldHolder& rho1,
                       volScalarFieldHolder& rho2,
                       volScalarFieldHolder& dgdt,
                       surfaceScalarFieldHolder& rhoPhi,
                       surfaceScalarFieldHolder& phi,
                       interfacePropertiesHolder& interface )
{
  label nAlphaCorr( readLabel( pimple->dict().lookup( "nAlphaCorr" ) ) );

  label nAlphaSubCycles( readLabel( pimple->dict().lookup( "nAlphaSubCycles" ) ) );

  smart_tmp< surfaceScalarField > phic( mag( phi() / mesh->magSf() ) );
  phic = min( interface->cAlpha() * phic(), max( phic() ) );

  smart_tmp< volScalarField > divU(fvc::div(phi));

  if (nAlphaSubCycles > 1)
  {
    dimensionedScalar totalDeltaT = runTime->deltaT();
    smart_tmp< surfaceScalarField > rhoPhiSum( 0.0 * rhoPhi );

    for( subCycle<volScalarField> alphaSubCycle(alpha1(), nAlphaSubCycles); !(++alphaSubCycle).end(); )
    {
      alphaEqns( runTime, mesh, interface, dgdt, alpha1, alpha2, divU, phic, phi, rhoPhi, rho1, rho2, nAlphaCorr );
      rhoPhiSum() += ( runTime->deltaT() / totalDeltaT ) * rhoPhi();
    }
    rhoPhi = rhoPhiSum;
  }
  else
  {
    alphaEqns( runTime, mesh, interface, dgdt, alpha1, alpha2, divU, phic, phi, rhoPhi, rho1, rho2, nAlphaCorr );
  }

  if ( pimple->corr() == 0 )
  {
    interface->correct();
  }
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_UEqn( const fvMeshHolder& mesh,
                               pimpleControlHolder& pimple,
                               volScalarFieldHolder& p_rgh,
                               volScalarFieldHolder& alpha1,
                               volScalarFieldHolder& rho,
                               surfaceScalarFieldHolder& rhoPhi,
                               surfaceScalarFieldHolder& phi,
                               volVectorFieldHolder& U,
                               surfaceScalarFieldHolder& ghf,
                               incompressible::turbulenceModelHolder& turbulence,
                               interfacePropertiesHolder& interface,
                               twoPhaseMixtureHolder& twoPhaseProperties )
{
  surfaceScalarFieldHolder muEff( "muEff",
                                  surfaceScalarFieldHolder( twoPhaseProperties->muf(), Deps( &twoPhaseProperties ) ) + 
                                  fvc::interpolate( rho * volScalarFieldHolder( turbulence->nut(), Deps( &turbulence ) ) ) );

  fvVectorMatrixHolder UEqn( fvm::ddt(rho, U) + fvm::div(rhoPhi, U) - 
                             fvm::laplacian(muEff, U) - ( fvc::grad( U ) & fvc::grad( muEff ) )
                             //- fvc::div(muEff*(fvc::interpolate(dev(fvc::grad(U))) & mesh.Sf())) 
                             );

  UEqn->relax();

  if ( pimple->momentumPredictor() )
  {
    solve( UEqn() == 
           fvc::reconstruct( ( fvc::interpolate( interface->sigmaK() ) * fvc::snGrad( alpha1() ) - 
                               ghf() * fvc::snGrad( rho() ) - fvc::snGrad( p_rgh() ) ) * mesh->magSf() ) );
  }
  
  return UEqn;
}

//---------------------------------------------------------------------------
void fun_pEqn( const TimeHolder& runTime,
               const fvMeshHolder& mesh,
               fvVectorMatrixHolder& UEqn,
               pimpleControlHolder& pimple,
               volScalarFieldHolder& p_rgh,
               volScalarFieldHolder& alpha1,
               volScalarFieldHolder& alpha2,
               volScalarFieldHolder& rho,
               volScalarFieldHolder& rho1,
               volScalarFieldHolder& rho2,
               volScalarFieldHolder& p,
               volScalarFieldHolder& dgdt,
               volScalarFieldHolder& gh,
               surfaceScalarFieldHolder& rhoPhi,
               surfaceScalarFieldHolder& phi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& ghf,
               interfacePropertiesHolder& interface,
               dimensionedScalar& psi1,
               dimensionedScalar& psi2,
               dimensionedScalar& rho10,
               dimensionedScalar& rho20,
               dimensionedScalar& pMin,
               int& corr )
{
  smart_tmp< volScalarField > rAU(1.0 / UEqn->A());
  smart_tmp< surfaceScalarField > rAUf( fvc::interpolate( rAU() ) );

  tmp<fvScalarMatrix> p_rghEqnComp;

  if ( pimple->transonic() )
  {
    p_rghEqnComp =( fvm::ddt( p_rgh() ) + fvm::div( phi(), p_rgh() ) - fvm::Sp( fvc::div( phi() ), p_rgh() ) );
  }
  else
  {
    p_rghEqnComp = ( fvm::ddt(p_rgh() ) + fvc::div( phi(), p_rgh() ) - fvc::Sp( fvc::div( phi() ), p_rgh() ) );
  }
  
  U = rAU() * UEqn->H();

  surfaceScalarField phiU( "phiU", 
                           ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) );

  phi = phiU + ( fvc::interpolate( interface->sigmaK() ) * fvc::snGrad( alpha1() ) - ghf() * fvc::snGrad( rho() ) ) * rAUf() * mesh->magSf();

  for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
  {

    smart_tmp< fvScalarMatrix > p_rghEqnIncomp( fvc::div( phi() ) - fvm::laplacian( rAUf(), p_rgh() ) );

    solve( ( max( alpha1(), scalar(0) ) * ( psi1 / rho1() ) + max( alpha2(), scalar( 0 ) ) * ( psi2 / rho2() ) ) * p_rghEqnComp() + 
               p_rghEqnIncomp(), 
             mesh->solver( p_rgh->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );

     if ( nonOrth == pimple->nNonOrthCorr() )
     {
       dgdt = ( pos( alpha2() ) * ( psi2 / rho2() ) - pos( alpha1() ) * ( psi1 / rho1() ) ) * ( p_rghEqnComp & p_rgh() );
       phi += p_rghEqnIncomp->flux();
     }
  }

  U += rAU() * fvc::reconstruct( ( phi() - phiU ) / rAUf() );
  U->correctBoundaryConditions();

  p = max( ( p_rgh() + gh() * ( alpha1() * rho10 + alpha2() *rho20 ) ) / 
             ( 1.0 - gh() * ( alpha1() * psi1 + alpha2() * psi2 ) ),  pMin );

  rho1 = rho10 + psi1 * p;
  rho2 = rho20 + psi2 * p;

  Info<< "max(U) " << max( mag(U() ) ).value() << endl;
  Info<< "min(p_rgh) " << min( p_rgh() ).value() << endl;
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  uniformDimensionedVectorFieldHolder g = readGravitationalAcceleration( runTime, mesh );

  pimpleControlHolder pimple(mesh);
  
  bool adjustTimeStep; scalar maxCo; scalar maxDeltaT; label nAlphaCorr; label nAlphaSubCycles; 
  readControls( runTime, pimple, args, adjustTimeStep, maxCo, maxDeltaT, nAlphaCorr, nAlphaSubCycles );
  
  scalar cumulativeContErr = initContinuityErrs();
  
  volScalarFieldHolder p_rgh; volScalarFieldHolder alpha1;
  volScalarFieldHolder alpha2; volVectorFieldHolder U;
  surfaceScalarFieldHolder phi; twoPhaseMixtureHolder twoPhaseProperties;
  volScalarFieldHolder gh; surfaceScalarFieldHolder ghf;
  volScalarFieldHolder p; volScalarFieldHolder rho1;
  volScalarFieldHolder rho2; volScalarFieldHolder rho;
  surfaceScalarFieldHolder rhoPhi; volScalarFieldHolder dgdt;
  interfacePropertiesHolder interface; incompressible::turbulenceModelHolder turbulence;
  
  result_createFields  res = createFields( runTime, mesh, g, p_rgh, alpha1, alpha2, U, phi, twoPhaseProperties, gh,
                                           ghf, p, rho1, rho2, rho, rhoPhi, dgdt, interface, turbulence );

  dimensionedScalar rho10 = res.m_rho10;
  dimensionedScalar rho20 = res.m_rho20;
  dimensionedScalar psi1= res.m_psi1;
  dimensionedScalar psi2 = res.m_psi2;
  dimensionedScalar pMin = res.m_pMin;
  
  scalar coNum; scalar meanCoNum;
  CourantNo( runTime, mesh, phi, coNum, meanCoNum );
  
  setInitialDeltaT( runTime, adjustTimeStep, maxCo, coNum );


  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  Info<< "\nStarting time loop\n" << endl;
  while (runTime->run())
  {
    readControls( runTime, pimple, args, adjustTimeStep, maxCo, maxDeltaT, nAlphaCorr, nAlphaSubCycles );
    CourantNo( runTime, mesh, phi, coNum, meanCoNum );
    setDeltaT( runTime, adjustTimeStep, maxCo, coNum, maxDeltaT );

    ( *runTime )++;

    Info<< "Time = " << runTime->timeName() << nl << endl;

    // --- Outer-corrector loop
    for (pimple->start(); pimple->loop(); (*pimple)++)
    {
      alphaEqnsSubCycle( runTime, mesh, pimple, alpha1, alpha2, rho, rho1, rho2, dgdt, rhoPhi, phi, interface );

      solve( fvm::ddt( rho() ) + fvc::div( rhoPhi() ) );

      fvVectorMatrixHolder UEqn = fun_UEqn( mesh, pimple, p_rgh, alpha1, rho, rhoPhi, phi, U, ghf, turbulence, interface, twoPhaseProperties );

      // --- PISO loop
      for (int corr=0; corr<pimple->nCorr(); corr++)
      {
        fun_pEqn( runTime, mesh, UEqn, pimple, p_rgh, alpha1, alpha2, rho, rho1, rho2, p, dgdt, gh, rhoPhi, phi, U, 
                  ghf, interface, psi1, psi2, rho10, rho20, pMin, corr);
      }

      if (pimple->turbCorr())
      {
        turbulence->correct();
      }
    }

    rho = alpha1 * rho1 + alpha2 * rho2;
    runTime->write();
    Info<< "ExecutionTime = "  << runTime->elapsedCpuTime() << " s\n\n" << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
