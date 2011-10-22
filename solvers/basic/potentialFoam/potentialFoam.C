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
    potentialFoam

Description
    Simple potential flow solver which can be used to generate starting fields
    for full Navier-Stokes codes.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

#include "core.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//---------------------------------------------------------------------------
int readControls( const fvMeshHolder& mesh, dictionary& potentialFlow )
{
  potentialFlow = mesh->solutionDict().subDict("potentialFlow");

  const int nNonOrthCorr = potentialFlow.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);
  
  return nNonOrthCorr;

}


//---------------------------------------------------------------------------
void createFields( const TimeHolder& runTime, const fvMeshHolder& mesh,
                   volScalarFieldHolder& p, volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi, label& pRefCell, scalar& pRefValue, 
                   dictionary& potentialFlow )
{
  Info<< "Reading field p\n" << endl;
  p( volScalarFieldHolder( IOobjectHolder( "p",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::NO_WRITE ),
                           mesh ) );

  p = dimensionedScalar("zero", p->dimensions(), 0.0);


  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  U = dimensionedVector("0", U->dimensions(), vector::zero);

  phi( surfaceScalarFieldHolder( IOobjectHolder( "phi",
                                                 runTime->timeName(),
                                                 mesh,
                                                 IOobject::NO_READ,
                                                 IOobject::AUTO_WRITE ),
                                 fvc::interpolate( U ) & surfaceVectorFieldHolder( mesh->Sf(), &mesh ) ) );


  pRefCell = 0;
  pRefValue = 0.0;
  setRefCell( p, potentialFlow, pRefCell, pRefValue );

}

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList::addBoolOption("writep", "write the final pressure field");

  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  dictionary potentialFlow;
  const int nNonOrthCorr = readControls( mesh, potentialFlow );
  
  volScalarFieldHolder p; volVectorFieldHolder U;
  surfaceScalarFieldHolder phi; label pRefCell; scalar pRefValue;
  createFields( runTime, mesh, p, U, phi, pRefCell, pRefValue, potentialFlow );

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< nl << "Calculating potential flow" << endl;

  // Since solver contains no time loop it would never execute
  // function objects so do it ourselves.
  runTime->functionObjects().start();

  adjustPhi(phi, U, p);

  for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
  {
    smart_tmp< fvScalarMatrix > pEqn( fvm::laplacian( dimensionedScalar( "1", dimTime / p->dimensions() * dimensionSet(0, 2, -2, 0, 0), 1 ), p() )
                                      == fvc::div( phi() ) );

    pEqn->setReference( pRefCell, pRefValue );
    pEqn->solve();

    if (nonOrth == nNonOrthCorr)
    {
      phi -= pEqn->flux();
    }
  }

  Info<< "continuity error = "
      << mag( fvc::div( phi() ))().weightedAverage( mesh->V() ).value() << endl;

  U = fvc::reconstruct( phi() );
  U->correctBoundaryConditions();

  Info<< "Interpolated U error = "
      << ( sqrt( sum(sqr( ( fvc::interpolate( U() ) & mesh->Sf()) - phi() ) ) ) / sum( mesh->magSf() ) ).value() << endl;

  // Force the write
  U->write();
  phi->write();

  if (args.optionFound("writep"))
  {
    p->write();
  }

  runTime->functionObjects().end();

  Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
      << "  ClockTime = " << runTime->elapsedClockTime() << " s"
      << nl << endl;

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
