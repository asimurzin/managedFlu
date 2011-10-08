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
    simpleFoam

Description
    Steady-state solver for incompressible, turbulent flow

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"

#include "singlePhaseTransportModelHolder.hpp"
#include "turbulenceModels/incompressible/RAS/RASModelHolder.hpp"
#include "simpleControlHolder.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
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
  p = volScalarFieldHolder( IOobjectHolder( "p",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ),
                            mesh );

  Info<< "Reading field U\n" << endl;
  U = volVectorFieldHolder( IOobjectHolder( "U",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ),
                            mesh );
  
  phi = createPhi( runTime, mesh, U );
  
  setRefCell( p, mesh->solutionDict().subDict("SIMPLE"), pRefCell, pRefValue );

  laminarTransport = singlePhaseTransportModelHolder( U, phi );

  turbulence = incompressible::RASModelHolder::New( U, phi, laminarTransport );

}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_UEqn( volVectorFieldHolder& U, 
                               const surfaceScalarFieldHolder& phi, 
                               const incompressible::RASModelHolder& turbulence,
                               const volScalarFieldHolder& p )
{
  // Solve the Momentum equation

  fvVectorMatrixHolder UEqn = fvm::div( phi, U ) + fvVectorMatrixHolder( turbulence->divDevReff( U() ), Deps( &turbulence, &U ) ) ;

  UEqn->relax();

  solve( UEqn == -fvc::grad( p ) );

  return UEqn;

}

//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               const simpleControlHolder& simple,               
               volVectorFieldHolder& U, 
               surfaceScalarFieldHolder& phi, 
               incompressible::RASModelHolder& turbulence,
               volScalarFieldHolder& p,
               fvVectorMatrixHolder& UEqn,
               label& pRefCell,
               scalar& pRefValue,
               scalar& cumulativeContErr )
{
  p->boundaryField().updateCoeffs();

  volScalarField rAU(1.0/UEqn().A());
  U() = rAU*UEqn().H();

  phi() = fvc::interpolate( U(), "interpolate(HbyA)") & mesh->Sf();
  adjustPhi(phi, U, p);

    // Non-orthogonal pressure corrector loop
  for (int nonOrth=0; nonOrth<=simple->nNonOrthCorr(); nonOrth++)
  {
    fvScalarMatrix pEqn( fvm::laplacian( rAU, p() ) == fvc::div( phi() ) );

    pEqn.setReference(pRefCell, pRefValue);

    pEqn.solve();

    if (nonOrth == simple->nNonOrthCorr())
    {
      phi() -= pEqn.flux();
    }
  }

  continuityErrors( runTime, mesh, phi, cumulativeContErr );

  // Explicitly relax pressure for momentum corrector
  p->relax();

  // Momentum corrector
  U() -= rAU * fvc::grad( p() );
  U().correctBoundaryConditions();
}



//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    argList args = setRootCase( argc, argv );
    
    TimeHolder runTime=createTime( Time::controlDictName, args );
    
    fvMeshHolder mesh = createMesh( runTime );
    
    volScalarFieldHolder p; volVectorFieldHolder U;
    surfaceScalarFieldHolder phi; singlePhaseTransportModelHolder laminarTransport;
    incompressible::RASModelHolder turbulence; 
    label pRefCell = 0;
    scalar pRefValue = 0.0;
    
    createFields( runTime, mesh, p, U, phi, laminarTransport, turbulence, pRefCell, pRefValue );


    scalar cumulativeContErr = initContinuityErrs();

    simpleControlHolder simple(mesh);

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (simple->loop())
    {
      Info<< "Time = " << runTime->timeName() << nl << endl;

      p->storePrevIter();

      // --- Pressure-velocity SIMPLE corrector
      {
        fvVectorMatrixHolder UEqn = fun_UEqn( U, phi, turbulence, p );
        fun_pEqn( mesh, runTime, simple, U, phi, turbulence, p, UEqn, pRefCell, pRefValue, cumulativeContErr );
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
