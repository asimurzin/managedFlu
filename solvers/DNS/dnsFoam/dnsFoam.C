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
    dnsFoam

Description
    Direct numerical simulation solver for boxes of isotropic turbulence

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fft.H"
#include "calcEk.H"
#include "graph.H"

#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "KmeshHolder.hpp"
#include "UOprocessHolder.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
dimensionedScalar readTransportProperties( const TimeHolder& runTime, const fvMeshHolder& mesh, 
                                           IOdictionaryHolder& transportProperties )
{
  Info<< "Reading transportProperties\n" << endl;

  transportProperties( IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                           runTime->constant(),
                                                           mesh,
                                                           IOobject::MUST_READ_IF_MODIFIED,
                                                           IOobject::NO_WRITE ) ) );

  return dimensionedScalar( transportProperties->lookup("nu") );
}


//---------------------------------------------------------------------------
void createFields( const TimeHolder& runTime, 
                   const fvMeshHolder& mesh,
                   volScalarFieldHolder& p, 
                   volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi )
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
}

//---------------------------------------------------------------------------
void readTurbulenceProperties( const TimeHolder& runTime, 
                               const fvMeshHolder& mesh,
                               const volVectorFieldHolder& U, 
                               IOdictionaryHolder& turbulenceProperties,
                               volVectorFieldHolder& force, 
                               KmeshHolder& K, 
                               UOprocessHolder& forceGen )
{
  Info<< "Reading turbulenceProperties\n" << endl;

  turbulenceProperties( IOdictionaryHolder( IOobjectHolder( "turbulenceProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) ) );

  force( volVectorFieldHolder( U / dimensionedScalar( "dt", dimTime, runTime->deltaTValue() ) ) );

  K( KmeshHolder( mesh ) );
  forceGen( UOprocessHolder( K, runTime->deltaTValue(), turbulenceProperties ) );
}


//---------------------------------------------------------------------------
void globalProperties( const TimeHolder& runTime,
                       const volVectorFieldHolder& U,
                       const volVectorFieldHolder& force,
                       const dimensionedScalar& nu )
{
  Info<< "k(" << runTime->timeName() << ") = " 
              << 3.0 / 2.0 * average( magSqr( U() ) ).value() << endl;
  
  Info << "epsilon(" << runTime->timeName() << ") = " 
       << ( 0.5 * nu * average ( magSqr( fvc::grad( U() ) + fvc::grad( U() )().T() ) ) ).value() << endl;

  Info<< "U.f("  << runTime->timeName() << ") = " << 181.0 * average( U() & force() ).value() << endl;
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMeshNoClear( runTime );
  
  IOdictionaryHolder transportProperties;
  
  dimensionedScalar nu = readTransportProperties( runTime, mesh, transportProperties );
  
  volScalarFieldHolder p; volVectorFieldHolder U;
  surfaceScalarFieldHolder phi;
  createFields( runTime, mesh, p, U, phi );
  
  IOdictionaryHolder turbulenceProperties; volVectorFieldHolder force;
  KmeshHolder K; UOprocessHolder forceGen;
  readTurbulenceProperties( runTime, mesh, U, turbulenceProperties, force, K, forceGen );
  
  scalar cumulativeContErr = initContinuityErrs();

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< nl << "Starting time loop" << endl;

  while (runTime->loop())
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;

    dictionary pisoDict; int nOuterCorr; int nCorr; int nNonOrthCorr;
    bool momentumPredictor; bool transonic;
    readPISOControls( mesh, pisoDict, nOuterCorr, nCorr, nNonOrthCorr, momentumPredictor, transonic);


    force->internalField() = ReImSum( fft::reverseTransform( K() /( mag( K() ) + 1.0e-6) ^ forceGen->newField(), K->nn() ) );
    
    globalProperties( runTime, U, force, nu );

    smart_tmp< fvVectorMatrix > UEqn( fvm::ddt( U() ) + fvm::div( phi(), U() ) - fvm::laplacian( nu, U() )
                                      == force() );

    solve( UEqn() == -fvc::grad( p() ) );

    // --- PISO loop
    for (int corr=1; corr<=1; corr++)
    {
      smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );

      U = rAU() * UEqn->H();
      phi = ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), U(), phi() );

      smart_tmp< fvScalarMatrix > pEqn( fvm::laplacian( rAU(), p() ) == fvc::div( phi() ) );

      pEqn->solve();

      phi -= pEqn->flux();

      continuityErrors( runTime, mesh, phi, cumulativeContErr );

      U -= rAU() * fvc::grad( p() );
      U->correctBoundaryConditions();
    }

    runTime->write();

    if ( runTime->outputTime() )
    {
      calcEk( U(), K() ).write( runTime->path()/"graphs"/runTime->timeName(),
                                "Ek",
                                runTime->graphFormat() );
    }

    Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
  }

  Info<< "End\n" << endl;
  return 0;
}


// ************************************************************************* //
