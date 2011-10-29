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
    porousSimpleFoam

Description
    Steady-state solver for incompressible, turbulent flow with
    implicit or explicit porosity treatment

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"

#include "singlePhaseTransportModelHolder.hpp"
#include "turbulenceModels/incompressible/RAS/RASModelHolder.hpp"
#include "simpleControlHolder.hpp"
#include "porousZonesHolder.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
void createFields( const TimeHolder& runTime, 
                   const fvMeshHolder& mesh,
                   volScalarFieldHolder& p,
                   volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi,
                   singlePhaseTransportModelHolder& laminarTransport,
                   incompressible::RASModelHolder& turbulence,
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
  
  setRefCell( p, mesh->solutionDict().subDict("SIMPLE"), pRefCell, pRefValue );

  laminarTransport = singlePhaseTransportModelHolder( U, phi );

  turbulence = incompressible::RASModelHolder::New( U, phi, laminarTransport );

}


//---------------------------------------------------------------------------
void createZones( fvMeshHolder& mesh, simpleControlHolder& simple,
                  porousZonesHolder& pZones, Switch& pressureImplicitPorosity, int& nUCorr )
{
  pZones = porousZonesHolder(mesh);
  pressureImplicitPorosity = false;
  
  // nUCorrectors used for pressureImplicitPorosity
  nUCorr = 0;
  if (pZones->size())
  {
    // nUCorrectors for pressureImplicitPorosity
    nUCorr = simple->dict().lookupOrDefault<int>("nUCorrectors", 0);

    if (nUCorr > 0)
    {
      pressureImplicitPorosity = true;
      Info<< "Using pressure implicit porosity" << endl;
    }
    else
    {
      Info<< "Using pressure explicit porosity" << endl;
    }
  }
}


//---------------------------------------------------------------------------
void fun_UEqn( fvVectorMatrixHolder& UEqn,
               volVectorFieldHolder& U,
               volScalarFieldHolder& p,
               volScalarFieldHolder& trAU,
               volTensorFieldHolder& trTU,
               surfaceScalarFieldHolder& phi,
               incompressible::RASModelHolder& turbulence,
               porousZonesHolder& pZones,
               Switch& pressureImplicitPorosity,
               int& nUCorr )
{
  // Construct the Momentum equation

  UEqn( fvm::div( phi, U ) + fvVectorMatrixHolder( turbulence->divDevReff( U() ), Deps( &turbulence, &U ) ) );
  UEqn->relax();

  // Include the porous media resistance and solve the momentum equation
  // either implicit in the tensorial resistance or transport using by
  // including the spherical part of the resistance in the momentum diagonal

  if (pressureImplicitPorosity)
  {
    volTensorFieldHolder tTU( tensor(I)*UEqn().A(), Deps( &UEqn ) );
    pZones->addResistance( UEqn(), tTU());
    trTU( volTensorFieldHolder( inv( tTU() ), Deps( &tTU ) ) );
    trTU->rename("rAU");

    smart_tmp< volVectorField > gradp( fvc::grad( p ) );

    for (int UCorr=0; UCorr<nUCorr; UCorr++)
    {
      U = trTU() & ( UEqn->H() - gradp() );
    }
    U->correctBoundaryConditions();
  }
  else
  {
    pZones->addResistance(UEqn());

    solve( UEqn == -fvc::grad( p ) );

    trAU( volScalarFieldHolder( 1.0 / UEqn->A(), Deps( &UEqn ) ) );
    trAU->rename("rAU");
  }

}

//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               const simpleControlHolder& simple,               
               volVectorFieldHolder& U, 
               surfaceScalarFieldHolder& phi, 
               incompressible::RASModelHolder& turbulence,
               volScalarFieldHolder& p,
               volScalarFieldHolder& trAU,
               volTensorFieldHolder& trTU,
               fvVectorMatrixHolder& UEqn,
               label& pRefCell,
               scalar& pRefValue,
               scalar& cumulativeContErr,
               Switch& pressureImplicitPorosity )

{
  if (pressureImplicitPorosity)
  {
    U = trTU() & UEqn->H();
  }
  else
  {
    U = trAU() * UEqn->H();
  }

  //UEqn.clear();
  phi = fvc::interpolate( U() ) & mesh->Sf();
  adjustPhi( phi, U, p );

  for (int nonOrth=0; nonOrth<=simple->nNonOrthCorr(); nonOrth++)
  {
    tmp<fvScalarMatrix> tpEqn;

    if (pressureImplicitPorosity)
    {
      tpEqn = ( fvm::laplacian( trTU(), p() ) == fvc::div( phi() ) );
    }
    else
    {
      tpEqn = ( fvm::laplacian( trAU(), p() ) == fvc::div( phi() ) );
    }

    tpEqn->setReference( pRefCell, pRefValue );
    // retain the residual from the first iteration
    if (nonOrth == 0)
    {
      tpEqn->solve();
    }
    else
    {
      tpEqn->solve();
    }

    if (nonOrth == simple->nNonOrthCorr())
    {
      phi -= tpEqn->flux();
    }
  }

  continuityErrors( runTime, mesh, phi, cumulativeContErr );

  // Explicitly relax pressure for momentum corrector
  p->relax();

  if (pressureImplicitPorosity)
  {
    U -= trTU() & fvc::grad( p() );
  }
  else
  {
    U -= trAU() * fvc::grad( p() );
  }

  U->correctBoundaryConditions();  
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  simpleControlHolder simple(mesh);
    
  volScalarFieldHolder p; volVectorFieldHolder U;
  surfaceScalarFieldHolder phi; singlePhaseTransportModelHolder laminarTransport;
  incompressible::RASModelHolder turbulence; fvVectorMatrixHolder UEqn;
  label pRefCell = 0;
  scalar pRefValue = 0.0;
    
  createFields( runTime, mesh, p, U, phi, laminarTransport, turbulence, pRefCell, pRefValue );

  porousZonesHolder pZones;
  Switch pressureImplicitPorosity;
  int nUCorr;
  
  createZones( mesh, simple, pZones, pressureImplicitPorosity, nUCorr );

  scalar cumulativeContErr = initContinuityErrs();
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;
  while (simple->loop())
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;

    p->storePrevIter();
    
    // Pressure-velocity SIMPLE corrector
    {
      fvVectorMatrixHolder UEqn;
      volScalarFieldHolder trAU;
      volTensorFieldHolder trTU;
      fun_UEqn( UEqn, U, p, trAU, trTU, phi, turbulence, pZones, pressureImplicitPorosity, nUCorr );
      
      fun_pEqn( mesh, runTime, simple, U, phi, turbulence, p, trAU, trTU, UEqn, pRefCell, pRefValue, 
                cumulativeContErr, pressureImplicitPorosity );
    }

    turbulence->correct();

    runTime->write();

    Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
