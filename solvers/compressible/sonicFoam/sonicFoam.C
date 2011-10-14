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
    sonicFoam

Description
    Transient solver for trans-sonic/supersonic, laminar or turbulent flow
    of a compressible gas.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "core.hpp"
#include "basicPsiThermoHolder.hpp"
#include "turbulenceModels/compressible/turbulenceModel/turbulenceModelHolder.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "compressibleContinuityErrs.hpp"
#include "compressibleCourantNo.hpp"
#include "compressibleCreatePhi.hpp"
#include "rhoEqn.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


void createFields( const TimeHolder& runTime,
                   const fvMeshHolder& mesh,
                   basicPsiThermoHolder& pThermo, 
                   volScalarFieldHolder& p,
                   volScalarFieldHolder& e,
                   volScalarFieldHolder& psi,
                   volScalarFieldHolder& rho,
                   volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi,
                   compressible::turbulenceModelHolder& turbulence )
{
  Info<< "Reading thermophysical properties\n" << endl;
  
  pThermo = basicPsiThermoHolder::New( mesh );

  p( volScalarFieldHolder( pThermo->p(), Deps( &pThermo ) ) );
  e( volScalarFieldHolder( pThermo->e(), Deps( &pThermo ) ) );
  psi( volScalarFieldHolder( pThermo->psi(), Deps( &pThermo ) ) );

  
  
  rho( volScalarFieldHolder( IOobjectHolder( "rho",
                                              runTime->timeName(),
                                              mesh ),
                              volScalarFieldHolder( pThermo->rho(), Deps( &pThermo ) ) ) );

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ), mesh ) );

  phi( compressibleCreatePhi( runTime, mesh, U, rho ) );

  Info<< "Creating turbulence model\n" << endl;
  turbulence = compressible::turbulenceModelHolder::New( rho, U, phi, pThermo );
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_Ueqn( const volScalarFieldHolder& rho,
                              volVectorFieldHolder& U, 
                              surfaceScalarFieldHolder& phi, 
                              const compressible::turbulenceModelHolder& turbulence,
                              const volScalarFieldHolder& p )
{
  fvVectorMatrixHolder UEqn = fvm::ddt( rho, U ) + fvm::div( phi, U ) + fvVectorMatrixHolder( turbulence->divDevRhoReff( U() ), Deps( &turbulence, &U ) );
  
  solve( UEqn == -fvc::grad( p ) );
  
  return UEqn;
}


//---------------------------------------------------------------------------
void fun_eEqn( volScalarFieldHolder& rho, 
               volScalarFieldHolder& e, 
               surfaceScalarFieldHolder& phi, 
               compressible::turbulenceModelHolder& turbulence,
               volScalarFieldHolder& p,
               basicPsiThermoHolder& thermo )
{
  solve(  fvm::ddt( rho(), e() ) + fvm::div( phi() , e() ) - fvm::laplacian( turbulence->alphaEff(), e() )  ==
          - p() * fvc::div( phi() / fvc::interpolate( rho() ) ) );

  thermo->correct();
}


//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               basicPsiThermoHolder& thermo,
               volScalarFieldHolder& rho,
               volScalarFieldHolder& p,
               volScalarFieldHolder& psi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& phi,
               compressible::turbulenceModelHolder& turbulence,
               fvVectorMatrixHolder& UEqn,
               scalar& cumulativeContErr,
               int& nNonOrthCorr )
               
{
  rho = thermo->rho();
  
  smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );
  
  U = rAU() * UEqn->H();
  
  surfaceScalarField phid( "phid",
                           fvc::interpolate( psi() ) * ( ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) ) );

  for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
  {
    smart_tmp< fvScalarMatrix > pEqn( fvm::ddt( psi(), p() ) + fvm::div( phid, p() ) - fvm::laplacian( rho() * rAU(), p() ) );

    pEqn->solve();

    if ( nonOrth == nNonOrthCorr )
    {
      phi = pEqn->flux();
    }
  }

  rhoEqn( rho, phi );
  
  compressibleContinuityErrs( thermo, rho, cumulativeContErr );

  U -= rAU() * fvc::grad( p() );
  U->correctBoundaryConditions();
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  basicPsiThermoHolder pThermo; volScalarFieldHolder p; volScalarFieldHolder e; volScalarFieldHolder psi; volScalarFieldHolder rho;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi; compressible::turbulenceModelHolder turbulence;
  
  createFields( runTime, mesh, pThermo, p, e, psi, rho, U, phi, turbulence );
  
  scalar cumulativeContErr = initContinuityErrs();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime->loop())
    {
        Info<< "Time = " << runTime->timeName() << nl << endl;

        dictionary pisoDict; int nOuterCorr; int nCorr; int nNonOrthCorr;
        bool momentumPredictor; bool transonic;
        readPISOControls( mesh, pisoDict, nOuterCorr, nCorr, nNonOrthCorr, momentumPredictor, transonic);
        
        scalar coNum, meanCoNum;
        compressibleCourantNo( runTime, mesh, phi, rho, coNum, meanCoNum );

        rhoEqn( rho, phi );

        fvVectorMatrixHolder UEqn = fun_Ueqn( rho, U, phi, turbulence, p );

        fun_eEqn( rho, e, phi, turbulence, p, pThermo );
        // --- PISO loop

        for (int corr=0; corr<nCorr; corr++)
        {
          fun_pEqn( mesh, runTime, pThermo, rho, p, psi, U, phi, turbulence, UEqn, cumulativeContErr, nNonOrthCorr );
        }

        turbulence->correct();

        rho = pThermo->rho();

        runTime->write();

        Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime->elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
