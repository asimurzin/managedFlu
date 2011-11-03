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
    interFoam

Description
    Solver for 2 incompressible, isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

    Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

    For a two-fluid approach see twoPhaseEulerFoam.

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
void createFields( const TimeHolder& runTime, const fvMeshHolder& mesh,
                   volScalarFieldHolder& p_rgh,
                   volScalarFieldHolder& alpha1,
                   volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi,
                   twoPhaseMixtureHolder& twoPhaseProperties,
                   volScalarFieldHolder& rho,
                   surfaceScalarFieldHolder& rhoPhi,
                   interfacePropertiesHolder& interface,
                   incompressible::turbulenceModelHolder& turbulence,
                   uniformDimensionedVectorFieldHolder& g,
                   volScalarFieldHolder& gh,
                   surfaceScalarFieldHolder& ghf,
                   volScalarFieldHolder& p,
                   label& pRefCell, scalar& pRefValue )
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

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  phi( createPhi( runTime, mesh, U ) );


  Info<< "Reading transportProperties\n" << endl;
  twoPhaseProperties( twoPhaseMixtureHolder( U, phi ) );
  
  const dimensionedScalar& rho1 = twoPhaseProperties->rho1();
  const dimensionedScalar& rho2 = twoPhaseProperties->rho2();

  // Need to store rho for ddt(rho, U)
  rho( volScalarFieldHolder( IOobjectHolder( "rho",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::READ_IF_PRESENT ),
                             alpha1 * rho1 + ( scalar( 1 ) - alpha1 ) * rho2,
                             alpha1->boundaryField().types() ) );
  rho->oldTime();
  // Mass flux
  // Initialisation does not matter because rhoPhi is reset after the
  // alpha1 solution before it is used in the U equation.
  rhoPhi( surfaceScalarFieldHolder( IOobjectHolder( "rho*phi",
                                                    runTime->timeName(),
                                                    mesh,
                                                    IOobject::NO_READ,
                                                    IOobject::NO_WRITE ),
                                    rho1 * phi ) );

  // Construct interface from alpha1 distribution
  interface( interfacePropertiesHolder( alpha1, U, twoPhaseProperties ) );

  // Construct incompressible turbulence model
  turbulence( incompressible::turbulenceModelHolder::New(U, phi, twoPhaseProperties) );

  g( readGravitationalAcceleration( runTime, mesh ) );

  /*
  dimensionedVector g0(g);

  // Read the data file and initialise the interpolation table
  interpolationTable<vector> timeSeriesAcceleration
  ( runTime.path()/runTime.caseConstant()/"acceleration.dat" );
  */

  Info<< "Calculating field g.h\n" << endl;
  gh( volScalarFieldHolder( "gh", g & volVectorFieldHolder( mesh->C(), Deps( &mesh ) ) ) );
  ghf( surfaceScalarFieldHolder( "ghf", g & surfaceVectorFieldHolder( mesh->Cf(), Deps( &mesh ) ) ) );

  p( volScalarFieldHolder( IOobjectHolder( "p",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::NO_READ,
                                           IOobject::AUTO_WRITE ),
                           p_rgh + rho*gh ) );

  pRefCell = 0;
  pRefValue = 0.0;
  setRefCell( p, p_rgh, mesh->solutionDict().subDict("PIMPLE"), pRefCell, pRefValue );

  if ( p_rgh->needReference() )
  {
    p += dimensionedScalar( "p", p->dimensions(), pRefValue - getRefCellValue( p, pRefCell ) );
    p_rgh = p - rho * gh;
  }
}


//---------------------------------------------------------------------------
void correctPhi( const TimeHolder& runTime, const fvMeshHolder& mesh,
                 pimpleControlHolder& pimple,
                 volScalarFieldHolder& p_rgh, 
                 volVectorFieldHolder& U,
                 surfaceScalarFieldHolder& phi,
                 volScalarFieldHolder& rho,
                 scalar& cumulativeContErr,
                 label& pRefCell, scalar& pRefValue )
{
  continuityErrors( runTime, mesh, phi, cumulativeContErr );
  
  wordList pcorrTypes( p_rgh->boundaryField().size(),
                       zeroGradientFvPatchScalarField::typeName );

  forAll (p_rgh->boundaryField(), i)
  {
    if ( p_rgh->boundaryField()[ i ].fixesValue())
    {
      pcorrTypes[ i ] = fixedValueFvPatchScalarField::typeName;
    }
  }

  volScalarField pcorr( IOobject( "pcorr",
                                  runTime->timeName(),
                                  *mesh,
                                  IOobject::NO_READ,
                                  IOobject::NO_WRITE ),
                        *mesh,
                        dimensionedScalar("pcorr", p_rgh->dimensions(), 0.0),
                        pcorrTypes );

  dimensionedScalar rAUf("(1|A(U))", dimTime / rho->dimensions(), 1.0);

  adjustPhi( phi(), U(), pcorr);

  for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
  {
    smart_tmp< fvScalarMatrix > pcorrEqn( fvm::laplacian( rAUf, pcorr ) == fvc::div( phi() ) );

    pcorrEqn->setReference(pRefCell, pRefValue);
    pcorrEqn->solve();
    

    if ( nonOrth == pimple->nNonOrthCorr())
    {
      phi -= pcorrEqn->flux();
    }
  }

  continuityErrors( runTime, mesh, phi, cumulativeContErr );
}


//---------------------------------------------------------------------------
void alphaCourantNo( const TimeHolder& runTime, const fvMeshHolder& mesh,
                     volScalarFieldHolder& alpha1,
                     surfaceScalarFieldHolder& phi,
                     scalar& alphaCoNum,
                     scalar& meanAlphaCoNum,
                     scalar& maxAlphaCo )
{
  maxAlphaCo = scalar( readScalar( runTime->controlDict().lookup( "maxAlphaCo" ) ) );
  
  alphaCoNum = 0.0;
  meanAlphaCoNum = 0.0;

  if (mesh->nInternalFaces())
  {
    scalarField sumPhi( pos( alpha1() - 0.01 ) * pos( 0.99 - alpha1() ) * fvc::surfaceSum( mag( phi() ))().internalField() );

    alphaCoNum = 0.5 * gMax( sumPhi / mesh->V().field() ) * runTime->deltaTValue();

    meanAlphaCoNum = 0.5 * ( gSum( sumPhi ) / gSum( mesh->V().field() ) ) * runTime->deltaTValue();
  }

  Info<< "Interface Courant Number mean: " << meanAlphaCoNum << " max: " << alphaCoNum << endl;
}


//---------------------------------------------------------------------------
void setDeltaT( TimeHolder& runTime, const scalar& maxCo, const scalar& CoNum,
                const scalar& alphaCoNum, const scalar& maxAlphaCo,
                const bool& adjustTimeStep, const scalar& maxDeltaT )
{
  if (adjustTimeStep)
  {
    scalar maxDeltaTFact = min( maxCo / ( CoNum + SMALL ), maxAlphaCo / ( alphaCoNum + SMALL ) );

    scalar deltaTFact = min( min( maxDeltaTFact, 1.0 + 0.1 * maxDeltaTFact ), 1.2 );

    runTime->setDeltaT( min( deltaTFact * runTime->deltaTValue(), maxDeltaT ) );

    Info<< "deltaT = " <<  runTime->deltaTValue() << endl;
  }
}


//---------------------------------------------------------------------------
void alphaEqn( const fvMeshHolder& mesh,
               volScalarFieldHolder& alpha1,
               surfaceScalarFieldHolder& rhoPhi,
               surfaceScalarFieldHolder& phi,
               interfacePropertiesHolder& interface,
               label& nAlphaCorr,
               const dimensionedScalar& rho1,
               const dimensionedScalar& rho2 )
{
  word alphaScheme( "div(phi,alpha)" );
  word alpharScheme( "div(phirb,alpha)" );

  smart_tmp< surfaceScalarField > phic( mag( phi() / mesh->magSf() ) );
  phic() = min( interface->cAlpha() * phic(), max( phic() ) );
  smart_tmp< surfaceScalarField > phir( phic() * interface->nHatf() );

  for (int aCorr=0; aCorr<nAlphaCorr; aCorr++)
  {
    smart_tmp< surfaceScalarField > phiAlpha( fvc::flux( phi(), alpha1(), alphaScheme ) + 
                                              fvc::flux( -fvc::flux( -phir(), scalar( 1 ) - alpha1(), alpharScheme ),
                                                         alpha1(),
                                                         alpharScheme ) );

    MULES::explicitSolve( alpha1(), phi(), phiAlpha(), 1, 0);

    rhoPhi = phiAlpha()*( rho1 - rho2) + phi() * rho2;
  }

    Info << "Liquid phase volume fraction = " << alpha1->weightedAverage( mesh->V() ).value() 
         << "  Min(alpha1) = " << min( alpha1() ).value()
        << "  Max(alpha1) = " << max( alpha1() ).value() << endl;
}


//---------------------------------------------------------------------------
void alphaEqnSubCycle( const TimeHolder& runTime, const fvMeshHolder& mesh,
                       pimpleControlHolder& pimple,
                       volScalarFieldHolder& alpha1,
                       volScalarFieldHolder& rho,
                       surfaceScalarFieldHolder& rhoPhi,
                       surfaceScalarFieldHolder& phi,
                       interfacePropertiesHolder& interface,
                       const dimensionedScalar& rho1,
                       const dimensionedScalar& rho2 )
{
  label nAlphaCorr( readLabel( pimple->dict().lookup( "nAlphaCorr" ) ) );

  label nAlphaSubCycles( readLabel( pimple->dict().lookup( "nAlphaSubCycles" ) ) );

  if (nAlphaSubCycles > 1)
  {
    dimensionedScalar totalDeltaT = runTime->deltaT();
    smart_tmp< surfaceScalarField > rhoPhiSum( 0.0 * rhoPhi );

    for( subCycle<volScalarField> alphaSubCycle( alpha1(), nAlphaSubCycles);
         !(++alphaSubCycle).end(); )
    {
      alphaEqn( mesh, alpha1, rhoPhi, phi, interface, nAlphaCorr, rho1, rho2 );
      rhoPhiSum() += ( runTime->deltaT() / totalDeltaT ) * rhoPhi();
    }

    rhoPhi = rhoPhiSum;
  }
  else
  {
    alphaEqn( mesh, alpha1, rhoPhi, phi, interface, nAlphaCorr, rho1, rho2 );
  }

  interface->correct();

  rho == alpha1 * rho1 + ( scalar( 1 ) - alpha1 ) * rho2;
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
               volScalarFieldHolder& rho,
               volScalarFieldHolder& p,
               volScalarFieldHolder& gh,
               surfaceScalarFieldHolder& rhoPhi,
               surfaceScalarFieldHolder& phi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& ghf,
               interfacePropertiesHolder& interface,
               int& corr,
               scalar& cumulativeContErr,
               label& pRefCell, scalar& pRefValue )
{
  smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );
  smart_tmp< surfaceScalarField > rAUf( fvc::interpolate( rAU() ) );

  U = rAU() * UEqn->H();
  surfaceScalarField phiU( "phiU",
                           ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) );

  adjustPhi(  phiU, U(), p_rgh() );

  phi = phiU + ( fvc::interpolate( interface->sigmaK() ) * fvc::snGrad( alpha1() ) - ghf() * fvc::snGrad( rho() ) ) * rAUf() *mesh->magSf();

  for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
  {
    smart_tmp< fvScalarMatrix > p_rghEqn( fvm::laplacian( rAUf(), p_rgh() ) == fvc::div( phi() ) );

    p_rghEqn->setReference( pRefCell, getRefCellValue( p_rgh, pRefCell ) );

    p_rghEqn->solve( mesh->solver( p_rgh->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );

    if (nonOrth == pimple->nNonOrthCorr())
    {
      phi -= p_rghEqn->flux();
    }
  }

  U += rAU() * fvc::reconstruct( ( phi() - phiU ) / rAUf() );
  U->correctBoundaryConditions();
  
  continuityErrors( runTime, mesh, phi, cumulativeContErr );

  p == p_rgh + rho*gh;

  if (p_rgh->needReference())
  {
    p += dimensionedScalar( "p",
                            p->dimensions(),
                            pRefValue - getRefCellValue( p, pRefCell ) );
    p_rgh = p - rho*gh;
  }
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );

  pimpleControlHolder pimple(mesh);

  scalar cumulativeContErr = initContinuityErrs();
  
  volScalarFieldHolder p_rgh; volScalarFieldHolder alpha1;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  twoPhaseMixtureHolder twoPhaseProperties; volScalarFieldHolder rho;
  surfaceScalarFieldHolder rhoPhi; interfacePropertiesHolder interface;
  incompressible::turbulenceModelHolder turbulence;
  uniformDimensionedVectorFieldHolder g;
  volScalarFieldHolder gh; surfaceScalarFieldHolder ghf;
  volScalarFieldHolder p;
  label pRefCell; scalar pRefValue;
  
  createFields( runTime, mesh, p_rgh, alpha1, U, phi, twoPhaseProperties, rho, rhoPhi, interface, turbulence, g, gh, ghf, p, pRefCell, pRefValue );
  const dimensionedScalar& rho1 = twoPhaseProperties->rho1();
  const dimensionedScalar& rho2 = twoPhaseProperties->rho2();
  
  bool adjustTimeStep; scalar maxCo; scalar maxDeltaT;
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );

  correctPhi( runTime, mesh, pimple, p_rgh, U, phi, rho, cumulativeContErr, pRefCell, pRefValue );

  scalar coNum; scalar meanCoNum;
  CourantNo( runTime, mesh, phi, coNum, meanCoNum );
  
  setInitialDeltaT( runTime, adjustTimeStep, maxCo, coNum );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;

  while (runTime->run())
  {
    readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
    CourantNo( runTime, mesh, phi, coNum, meanCoNum );
    
    scalar alphaCoNum; scalar meanAlphaCoNum; scalar maxAlphaCo;
    alphaCourantNo( runTime, mesh, alpha1, phi, alphaCoNum, meanAlphaCoNum, maxAlphaCo );
    
    setDeltaT( runTime, maxCo, coNum, alphaCoNum, maxAlphaCo, adjustTimeStep, maxDeltaT );

    (*runTime)++;

    Info<< "Time = " << runTime->timeName() << nl << endl;

    twoPhaseProperties->correct();
    
    alphaEqnSubCycle( runTime, mesh, pimple, alpha1, rho, rhoPhi, phi, interface, rho1, rho2 );
    
    fvVectorMatrixHolder UEqn = fun_UEqn( mesh, pimple, p_rgh, alpha1, rho, rhoPhi, phi, U, ghf, turbulence, interface, twoPhaseProperties );
    // --- Pressure-velocity PIMPLE corrector loop
    for (pimple->start(); pimple->loop(); (*pimple)++)
    {
      fvVectorMatrixHolder UEqn = fun_UEqn( mesh, pimple, p_rgh, alpha1, rho, rhoPhi, phi, U, ghf, turbulence, interface, twoPhaseProperties );

      // --- PISO loop
      for (int corr=0; corr<pimple->nCorr(); corr++)
      {
        fun_pEqn( runTime, mesh, UEqn, pimple, p_rgh, alpha1, rho, p, gh, rhoPhi, 
                  phi, U, ghf, interface, corr, cumulativeContErr, pRefCell, pRefValue );
      }
 
      if (pimple->turbCorr())
      {
        turbulence->correct();
      }
   }

   runTime->write();

   Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime->elapsedClockTime() << " s"
        << nl << endl;
  }

  Info<< "End\n" << endl;
 
  return 0;
}


// ************************************************************************* //
