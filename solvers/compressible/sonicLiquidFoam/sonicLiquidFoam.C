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
    sonicLiquidFoam

Description
    Transient solver for trans-sonic/supersonic, laminar flow of a
    compressible liquid.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "core.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "compressibleCreatePhi.hpp"
#include "compressibleCourantNo.hpp"
#include "rhoEqn.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
struct result_readThermodynamicProperties
{
  dimensionedScalar m_rho0;
  dimensionedScalar m_p0;
  dimensionedScalar m_psi;
  dimensionedScalar m_rhoO;
  result_readThermodynamicProperties( dimensionedScalar the_rho0, dimensionedScalar the_p0, dimensionedScalar the_psi, dimensionedScalar the_rhoO )
    : m_rho0( the_rho0 )
    , m_p0( the_p0 )
    , m_psi( the_psi )
    , m_rhoO( the_rhoO )
  {}
};


//---------------------------------------------------------------------------
result_readThermodynamicProperties readThermodynamicProperties( const TimeHolder& runTime, 
                                                                const fvMeshHolder& mesh,
                                                                IOdictionaryHolder& thermodynamicProperties )
{
  Info<< "Reading thermodynamicProperties\n" << endl;

  thermodynamicProperties = IOdictionaryHolder( IOobjectHolder( "thermodynamicProperties",
                                                                runTime->constant(),
                                                                mesh,
                                                                IOobject::MUST_READ_IF_MODIFIED,
                                                                IOobject::NO_WRITE ) );

  dimensionedScalar rho0( thermodynamicProperties->lookup("rho0") );
  dimensionedScalar p0( thermodynamicProperties->lookup("p0") );
  dimensionedScalar psi(thermodynamicProperties->lookup("psi") );

  // Density offset, i.e. the constant part of the density
  dimensionedScalar rhoO("rhoO", rho0 - psi*p0);
  
  return result_readThermodynamicProperties( rho0, p0, psi, rhoO );
}


//---------------------------------------------------------------------------
dimensionedScalar readTransportProperties ( const TimeHolder& runTime, 
                                            const fvMeshHolder& mesh,
                                            IOdictionaryHolder& transportProperties )
{
  Info<< "Reading transportProperties\n" << endl;

  transportProperties = IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) );

  dimensionedScalar mu( transportProperties->lookup( "mu" ) );
  
  return mu;
}


//---------------------------------------------------------------------------
void createFields( const TimeHolder& runTime, const fvMeshHolder& mesh, 
                   volScalarFieldHolder& rho, volScalarFieldHolder& p,
                   volVectorFieldHolder& U, surfaceScalarFieldHolder& phi,
                   dimensionedScalar rhoO, dimensionedScalar psi )
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

  rho( volScalarFieldHolder( IOobjectHolder( "rho",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::NO_READ,
                                             IOobject::AUTO_WRITE ),
                             rhoO + psi*p ) );
  
  phi( compressibleCreatePhi( runTime, mesh, U, rho ) );
  
}

//---------------------------------------------------------------------------
void compressibleContinuityErrs( volScalarFieldHolder& rho, surfaceScalarFieldHolder& phi,
                                 volScalarFieldHolder& p, dimensionedScalar& rho0,
                                 dimensionedScalar& p0, dimensionedScalar& psi,
                                 scalar& cumulativeContErr )
{  
  rhoEqn( rho, phi );
  
  scalar sumLocalContErr = ( sum( mag( rho() - rho0 - psi * ( p() - p0 ) ) ) / sum( rho() ) ).value();

  scalar globalContErr = (sum( rho() - rho0 - psi * ( p() - p0 ) ) / sum( rho() ) ).value();

  cumulativeContErr += globalContErr;

  Info << "time step continuity errors : sum local = " << sumLocalContErr
       << ", global = " << globalContErr
       << ", cumulative = " << cumulativeContErr << endl;
}

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  IOdictionaryHolder thermodynamicProperties;
  result_readThermodynamicProperties res =  readThermodynamicProperties( runTime, mesh, thermodynamicProperties );
  
  dimensionedScalar rho0 =  res.m_rho0;
  dimensionedScalar p0 =  res.m_p0;
  dimensionedScalar psi = res.m_psi;
  dimensionedScalar rhoO = res.m_rhoO;
  
  IOdictionaryHolder transportProperties;
  dimensionedScalar mu = readTransportProperties( runTime, mesh, transportProperties );

  volScalarFieldHolder rho; volScalarFieldHolder p;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  
  createFields( runTime, mesh, rho, p, U, phi, rhoO, psi );
  
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

    fvVectorMatrixHolder UEqn( fvm::ddt( rho, U ) + fvm::div( phi, U ) - fvm::laplacian( mu, U ) );

    solve(UEqn == -fvc::grad(p));


    // --- PISO loop
    for (int corr=0; corr<nCorr; corr++)
    {
      smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );
      U = rAU() * UEqn->H();

      surfaceScalarField phid( "phid", psi * ( ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) ) );

      phi = ( rhoO / psi ) * phid;

      smart_tmp< fvScalarMatrix > pEqn( fvm::ddt( psi, p() ) + fvc::div( phi() ) + fvm::div( phid, p() ) - fvm::laplacian( rho() * rAU(), p() ) );

      pEqn->solve();

      phi += pEqn->flux();
        
      compressibleContinuityErrs( rho, phi, p, rho0, p0, psi, cumulativeContErr );
        
      U -= rAU() * fvc::grad( p() );
      U->correctBoundaryConditions();
    }
    rho = rhoO + psi*p;

    runTime->write();

    Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
