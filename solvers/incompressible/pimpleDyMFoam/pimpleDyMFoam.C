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
    pimpleDyMFoam.C

Description
    Transient solver for incompressible, flow of Newtonian fluids
    on a moving mesh using the PIMPLE (merged PISO-SIMPLE) algorithm.

    Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "turbulenceModels/incompressible/turbulenceModel/turbulenceModelHolder.hpp"
#include "singlePhaseTransportModelHolder.hpp"
#include "dynamicFvMeshHolder.hpp"
#include "pimpleControlHolder.hpp"

#include "createDynamicFvMesh.hpp"
#include "meshCourantNo.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void createFields( const TimeHolder& runTime, 
                   const fvMeshHolder& mesh,
                   volScalarFieldHolder& p,
                   volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi,
                   singlePhaseTransportModelHolder& laminarTransport,
                   incompressible::turbulenceModelHolder& turbulence,
                   volScalarFieldHolder& rAU,
                   label& pRefCell,
                   scalar& pRefValue )
{
  Info<< "Reading field p\n" << endl;
  p( volScalarFieldHolder( IOobjectHolder( "p",
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


  pRefCell = 0;
  pRefValue = 0.0;
  setRefCell(p, mesh->solutionDict().subDict("PIMPLE"), pRefCell, pRefValue);

  laminarTransport( singlePhaseTransportModelHolder( U, phi ) );

  turbulence( incompressible::turbulenceModelHolder::New( U, phi, laminarTransport ) );

  Info<< "Reading field rAU if present\n" << endl;
  rAU( volScalarFieldHolder( IOobjectHolder( "rAU",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::READ_IF_PRESENT,
                                             IOobject::AUTO_WRITE ),
                             mesh,
                             runTime->deltaT(),
                             zeroGradientFvPatchScalarField::typeName ) );
}


//---------------------------------------------------------------------------
void readControls( const pimpleControlHolder& pimple, 
                   const TimeHolder& runTime, 
                   bool& adjustTimeStep, 
                   scalar& maxCo, 
                   scalar& maxDeltaT, 
                   bool& correctPhi, 
                   bool& checkMeshCourantNo )
{
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
  const dictionary& pimpleDict = pimple->dict();

  correctPhi = pimpleDict.lookupOrDefault("correctPhi", false);
  checkMeshCourantNo = pimpleDict.lookupOrDefault("checkMeshCourantNo", false);
}


//---------------------------------------------------------------------------
void fun_correctPhi( const TimeHolder& runTime,
                     fvMeshHolder& mesh,
                     pimpleControlHolder& pimple,
                     volScalarFieldHolder& p,
                     volScalarFieldHolder& rAU,
                     volVectorFieldHolder& U,
                     surfaceScalarFieldHolder& phi,
                     scalar& cumulativeContErr,
                     label& pRefCell, scalar& pRefValue )
{
  if (mesh->changing())
  {
    forAll(U->boundaryField(), patchi)
    {
      if (U->boundaryField()[patchi].fixesValue())
      {
        U->boundaryField()[patchi].initEvaluate();
      }
    }

    forAll(U->boundaryField(), patchi)
    {
      if (U->boundaryField()[patchi].fixesValue())
      {
        U->boundaryField()[patchi].evaluate();
        phi->boundaryField()[patchi] = U->boundaryField()[patchi] & mesh->Sf().boundaryField()[patchi];
      }
    }
  }

  wordList pcorrTypes( p->boundaryField().size(), zeroGradientFvPatchScalarField::typeName );

  forAll(p->boundaryField(), i) 
  {
    if (p->boundaryField()[i].fixesValue())
    {
      pcorrTypes[i] = fixedValueFvPatchScalarField::typeName;
    }
  }

  volScalarField pcorr( IOobject( "pcorr",
                                  runTime->timeName(),
                                  *mesh,
                                  IOobject::NO_READ,
                                  IOobject::NO_WRITE ),
                        *mesh,
                        dimensionedScalar("pcorr", p->dimensions(), 0.0),
                        pcorrTypes );

  for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
  {
     smart_tmp< fvScalarMatrix > pcorrEqn( fvm::laplacian( rAU(), pcorr) == fvc::div( phi() ) );

     pcorrEqn->setReference(pRefCell, pRefValue);
     pcorrEqn->solve();

     if (nonOrth == pimple->nNonOrthCorr())
     {
       phi -= pcorrEqn->flux();
     }
  }

  continuityErrors( runTime, mesh, phi, cumulativeContErr );
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_UEqn( const pimpleControlHolder& pimple,
                               volVectorFieldHolder& U, 
                               const surfaceScalarFieldHolder& phi, 
                               const incompressible::turbulenceModelHolder& turbulence,
                               const volScalarFieldHolder& p,
                               volScalarFieldHolder& rAU )
{
  fvVectorMatrixHolder UEqn( fvm::ddt( U ) + fvm::div(phi, U) + fvVectorMatrixHolder( turbulence->divDevReff( U() ), Deps( &turbulence, &U ) ) );

  UEqn->relax();

  rAU = 1.0 / UEqn->A();

  if (pimple->momentumPredictor())
  {
    solve( UEqn() == -fvc::grad( p() ) );
  }
  else
  {
    U = rAU() *( UEqn->H() - fvc::grad( p() ) );
    U->correctBoundaryConditions();
  }

  return UEqn;
}


//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               const pimpleControlHolder& pimple,
               volVectorFieldHolder& U, 
               surfaceScalarFieldHolder& phi, 
               incompressible::turbulenceModelHolder& turbulence,
               volScalarFieldHolder& p,
               volScalarFieldHolder& rAU,
               fvVectorMatrixHolder& UEqn,
               label& pRefCell,
               scalar& pRefValue,
               scalar& cumulativeContErr,
               int& corr )
{
  U = rAU() * UEqn->H();

  if (pimple->nCorr() <= 1)
  {
    //UEqn.clear();
  }

  phi = ( fvc::interpolate( U() ) & mesh->Sf() );

  if (p->needReference())
  {
    fvc::makeRelative( phi(), U() );
    adjustPhi( phi(), U(), p() );
    fvc::makeAbsolute( phi(), U() );
  }

  for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
  {
    smart_tmp< fvScalarMatrix > pEqn( fvm::laplacian( rAU(), p() ) == fvc::div( phi() ) );

    pEqn->setReference(pRefCell, pRefValue);

    pEqn->solve( mesh->solver( p->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );

    if (nonOrth == pimple->nNonOrthCorr() )
    {
        phi -= pEqn->flux();
    }
  }

  continuityErrors( runTime, mesh, phi, cumulativeContErr );

  // Explicitly relax pressure for momentum corrector
  p->relax();

  // Make the fluxes relative to the mesh motion
  fvc::makeRelative( phi(), U() );

  U -= rAU() * fvc::grad( p() );
  U->correctBoundaryConditions();
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  dynamicFvMeshHolder mesh = createDynamicFvMesh( runTime );
  
  scalar cumulativeContErr = initContinuityErrs();
  
  volScalarFieldHolder p; volVectorFieldHolder U;
  surfaceScalarFieldHolder phi; singlePhaseTransportModelHolder laminarTransport;
  incompressible::turbulenceModelHolder turbulence; volScalarFieldHolder rAU;
  label pRefCell; scalar pRefValue;
  createFields( runTime, mesh, p, U, phi, laminarTransport, turbulence, rAU, pRefCell, pRefValue );
  
  bool adjustTimeStep; scalar maxCo; scalar maxDeltaT;
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
  
  pimpleControlHolder pimple(mesh);  

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;
  while ( runTime->run() )
  {
    bool  correctPhi, checkMeshCourantNo;
    readControls( pimple, runTime, adjustTimeStep, maxCo, maxDeltaT, correctPhi, checkMeshCourantNo );

    scalar coNum; scalar meanCoNum;
    CourantNo( runTime, mesh, phi, coNum, meanCoNum );

    // Make the fluxes absolute
    fvc::makeAbsolute( phi(), U() );

    setDeltaT( runTime, adjustTimeStep, maxCo, coNum, maxDeltaT );

    ( *runTime )++;

    Info<< "Time = " << runTime->timeName() << nl << endl;

    mesh->update();

    if (mesh->changing() && correctPhi)
    {
      fun_correctPhi( runTime, mesh,pimple, p, rAU, U, phi, cumulativeContErr, pRefCell, pRefValue );
    }

    // Make the fluxes relative to the mesh motion
    fvc::makeRelative( phi(), U() );

    if (mesh->changing() && checkMeshCourantNo)
    {
      scalar meshCoNum; scalar meanMeshCoNum;
      meshCourantNo( runTime, mesh, phi, meshCoNum, meanMeshCoNum );
    }


    // --- Pressure-velocity PIMPLE corrector loop
    for (pimple->start(); pimple->loop(); (*pimple)++)
    {

      if (pimple->nOuterCorr() != 1)
      {
        p->storePrevIter();
      }
      
      fvVectorMatrixHolder UEqn = fun_UEqn( pimple, U, phi, turbulence, p, rAU );
      
       // --- PISO loop
       for (int corr=0; corr < pimple->nCorr(); corr++)
       {
         fun_pEqn( mesh, runTime, pimple, U, phi, turbulence, p, rAU, UEqn, pRefCell, pRefValue, cumulativeContErr, corr );
       }
       if (pimple->turbCorr())
       {
         turbulence->correct();
       }
    } 

    runTime->write();

    Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
