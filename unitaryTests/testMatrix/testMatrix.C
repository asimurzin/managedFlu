/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2010 OpenCFD Ltd.
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
    icoFoam

Description
    Transient solver for incompressible, laminar flow of Newtonian fluids.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "core.hpp"
#include "Allfunctions.hpp"


//---------------------------------------------------------------------------
dimensionedScalar createFields( const TimeHolder& runTime, 
                                const fvMeshHolder& mesh,
                                IOdictionaryHolder& transportProperties,
                                volScalarFieldHolder& p,
                                volVectorFieldHolder& U,
                                surfaceScalarFieldHolder& phi,
                                label& pRefCell,
                                scalar& pRefValue )
{
  Info<< "Reading transportProperties\n" << endl;

  transportProperties = IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) );

  dimensionedScalar nu ( transportProperties->lookup("nu") );

  Info << "Reading field p\n" << endl;
  
  p( volScalarFieldHolder( IOobjectHolder( "p",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ), mesh ) );

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ), mesh ) );

    
  phi( createPhi( runTime, mesh, U ) );
  
  setRefCell( p, mesh->solutionDict().subDict("PISO"), pRefCell, pRefValue);

  return nu;
} 


//---------------------------------------------------------------------------
fvVectorMatrixHolder createMatrix(int argc, char *argv[])
//fvVectorMatrix createMatrix(int argc, char *argv[])
{
    argList args = setRootCase( argc, argv );
    
    TimeHolder runTime=createTime( Time::controlDictName, args );
    
    fvMeshHolder mesh = createMesh( runTime );
    
    IOdictionaryHolder transportProperties;
    volScalarFieldHolder p;
    volVectorFieldHolder U;
    surfaceScalarFieldHolder phi;
    label pRefCell = 0;
    scalar pRefValue = 0.0;
    
    dimensionedScalar nu = createFields( runTime, mesh, transportProperties, p, U, phi, pRefCell, pRefValue );


    scalar cumulativeContErr = initContinuityErrs();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    runTime->loop();
    Info<< "Time = " << runTime->timeName() << nl << endl;
     
    dictionary pisoDict; int nOuterCorr; int nCorr; int nNonOrthCorr;
    bool momentumPredictor; bool transonic;
    readPISOControls( mesh, pisoDict, nOuterCorr, nCorr, nNonOrthCorr, momentumPredictor, transonic);
      
    //CourantNo( runTime, mesh, phi );

    fvVectorMatrixHolder UEqn = fvm::ddt( U ) + fvm::div( phi, U ) - fvm::laplacian( nu, U );
    
    // fvVectorMatrix UEqn = fvm::ddt( U() ) + fvm::div( phi(), U() ) - fvm::laplacian( nu, U() );
    
    return UEqn;

}
int main(int argc, char *argv[])
{
    fvVectorMatrixHolder UEqn = createMatrix( argc, argv);
    //fvVectorMatrix UEqn = createMatrix( argc, argv);
    //solve( UEqn );
    Info<< "UEqn() = " << UEqn().psi() << endl;
    //Info<< "UEqn() = " << UEqn.psi() << endl;
    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
