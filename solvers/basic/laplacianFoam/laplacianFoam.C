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
    laplacianFoam

Description
    Solves a simple Laplace equation, e.g. for thermal diffusion in a solid.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "simpleControl.H"

#include "core.hpp"
#include "simpleControlHolder.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
dimensionedScalar createFields( const TimeHolder& runTime, const fvMeshHolder& mesh,
                                IOdictionaryHolder& transportProperties, volScalarFieldHolder& T )
{
  Info<< "Reading field T\n" << endl;

  T( volScalarFieldHolder( IOobjectHolder( "T",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ),
                           mesh ) );


  Info<< "Reading transportProperties\n" << endl;
  
  transportProperties = IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) );


  Info<< "Reading diffusivity DT\n" << endl;

  dimensionedScalar DT( transportProperties->lookup("DT") );
  
  return DT;
}


//---------------------------------------------------------------------------
void write( const TimeHolder& runTime, const fvMeshHolder& mesh, volScalarFieldHolder& T )
{
  if (runTime->outputTime())
  {
    smart_tmp< volVectorField > gradT( fvc::grad( T ) );

    volScalarField gradTx( IOobject( "gradTx",
                                     runTime->timeName(),
                                     *mesh,
                                     IOobject::NO_READ,
                                     IOobject::AUTO_WRITE ),
                           gradT->component( vector::X ) );

    volScalarField gradTy( IOobject( "gradTy",
                                     runTime->timeName(),
                                     *mesh,
                                     IOobject::NO_READ,
                                     IOobject::AUTO_WRITE ),
                           gradT->component( vector::Y ) );
    
    volScalarField gradTz( IOobject( "gradTz",
                                     runTime->timeName(),
                                     *mesh,
                                     IOobject::NO_READ,
                                     IOobject::AUTO_WRITE ),
                           gradT->component(vector::Z) );


    runTime->write();
  }
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  IOdictionaryHolder transportProperties; volScalarFieldHolder T;
  dimensionedScalar DT = createFields( runTime, mesh, transportProperties, T );

  simpleControlHolder simple(mesh);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nCalculating temperature distribution\n" << endl;

  while ( simple->loop() )
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;
    
    for (int nonOrth=0; nonOrth<=simple->nNonOrthCorr(); nonOrth++)
    {
      solve( fvm::ddt( T() ) - fvm::laplacian( DT, T() ) );
    }

    write( runTime, mesh, T );

    Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
