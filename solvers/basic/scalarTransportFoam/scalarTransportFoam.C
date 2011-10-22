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
    scalarTransportFoam

Description
    Solves a transport equation for a passive scalar

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
                                IOdictionaryHolder& transportProperties, volScalarFieldHolder& T,
                                volVectorFieldHolder& U, surfaceScalarFieldHolder& phi )
{
  Info<< "Reading field T\n" << endl;

  T( volScalarFieldHolder( IOobjectHolder( "T",
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
  Info<< "Reading transportProperties\n" << endl;
  
  transportProperties = IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) );


  Info<< "Reading diffusivity D\n" << endl;

  dimensionedScalar DT( transportProperties->lookup("DT") );
  
  phi( createPhi( runTime, mesh, U ) );
  
  return DT;
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  IOdictionaryHolder transportProperties; volScalarFieldHolder T;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  dimensionedScalar DT = createFields( runTime, mesh, transportProperties, T, U, phi );

  simpleControlHolder simple(mesh);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nCalculating scalar transport\n" << endl;

  scalar CoNum; scalar meanCoNum;
  CourantNo( runTime, mesh, phi, CoNum, meanCoNum );

  while (simple->loop())
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;

    for (int nonOrth=0; nonOrth<=simple->nNonOrthCorr(); nonOrth++)
    {
      solve( fvm::ddt( T() ) + fvm::div( phi(), T() ) - fvm::laplacian( DT, T() ) );
    }

    runTime->write();
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
