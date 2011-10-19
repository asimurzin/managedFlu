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
    rhoPorousMRFPimpleFoam

Description
    Transient solver for laminar or turbulent flow of compressible fluids
    with support for porous media and MRF for HVAC and similar applications.

    Uses the flexible PIMPLE (PISO-SIMPLE) solution for time-resolved and
    pseudo-transient simulations.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "basicPsiThermo.H"
#include "turbulenceModel.H"
#include "bound.H"
#include "MRFZones.H"
#include "porousZones.H"
#include "pimpleControl.H"

#include "core.hpp"
#include "pimpleControlHolder.hpp"
#include "MRFZonesHolder.hpp"
#include "porousZonesHolder.hpp"
#include "basicRhoThermoHolder.hpp"
#include "turbulenceModels/compressible/turbulenceModel/turbulenceModelHolder.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "compressibleContinuityErrs.hpp"
#include "compressibleCreatePhi.hpp"
#include "compressibleCourantNo.hpp"
#include "rhoEqn.hpp"

//---------------------------------------------------------------------------
struct result_createFields
{
  dimensionedScalar m_rhoMax;
  dimensionedScalar m_rhoMin;
  result_createFields( dimensionedScalar the_rhoMax, dimensionedScalar the_rhoMin )
    : m_rhoMax( the_rhoMax )
    , m_rhoMin( the_rhoMin )
  {}
};


//---------------------------------------------------------------------------
result_createFields createFields( const TimeHolder& runTime, const fvMeshHolder& mesh,
                                  basicPsiThermoHolder& pThermo, volScalarFieldHolder& rho,
                                  volScalarFieldHolder& p, volScalarFieldHolder& h,
                                  volScalarFieldHolder& psi, volVectorFieldHolder& U,
                                  surfaceScalarFieldHolder& phi, compressible::turbulenceModelHolder& turbulence,
                                  volScalarFieldHolder& DpDt )
{
  Info<< "Reading thermophysical properties\n" << endl;

  pThermo = basicPsiThermoHolder::New(mesh);

  p( volScalarFieldHolder( pThermo->p(), Deps( &pThermo ) ) );
  h( volScalarFieldHolder( pThermo->h(), Deps( &pThermo ) ) );
  psi( volScalarFieldHolder( pThermo->psi(), Deps( &pThermo ) ) );

  rho( volScalarFieldHolder( IOobjectHolder( "rho",
                                              runTime->timeName(),
                                              mesh,
                                              IOobject::READ_IF_PRESENT,
                                              IOobject::AUTO_WRITE ),
                              volScalarFieldHolder( pThermo->rho(), Deps( &pThermo ) ) ) );

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  phi( compressibleCreatePhi( runTime, mesh, U, rho ) );

  dimensionedScalar rhoMax( mesh->solutionDict().subDict("PIMPLE").lookup("rhoMax") );

  dimensionedScalar rhoMin( mesh->solutionDict().subDict("PIMPLE").lookup("rhoMin") );

  Info<< "Creating turbulence model\n" << endl;
  turbulence = compressible::turbulenceModelHolder::New( rho, U, phi, pThermo );
  
  Info<< "Creating field DpDt\n" << endl;
  DpDt( fvc::DDt( surfaceScalarFieldHolder( "phiU", phi / fvc::interpolate( rho ) ), p) );
  
  return result_createFields( rhoMax, rhoMin );
}


//---------------------------------------------------------------------------
void createZones( fvMeshHolder& mesh, volVectorFieldHolder& U,
                  MRFZonesHolder& mrfZones, porousZonesHolder& pZones, Switch& pressureImplicitPorosity )
{
  mrfZones = MRFZonesHolder( mesh );
  mrfZones->correctBoundaryVelocity( U() );

  pZones = porousZonesHolder(mesh);
  pressureImplicitPorosity = false;
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_Ueqn( const pimpleControlHolder& pimple,
                               const volScalarFieldHolder& rho,
                               const volScalarFieldHolder& p,
                               volVectorFieldHolder& U, 
                               const surfaceScalarFieldHolder& phi, 
                               const compressible::turbulenceModelHolder& turbulence,
                               MRFZonesHolder& mrfZones, porousZonesHolder& pZones )
{
  fvVectorMatrixHolder UEqn( fvm::ddt( rho, U ) + fvm::div( phi, U ) + fvVectorMatrixHolder( turbulence->divDevRhoReff( U() ), Deps( &turbulence, &U ) ) );
  
  UEqn->relax();
  
  mrfZones->addCoriolis( rho(), UEqn() );
  pZones->addResistance( UEqn() );
  
  smart_tmp< volScalarField >  rAU( 1.0 / UEqn->A() );
  
  if ( pimple->momentumPredictor() )
  {
    solve( UEqn == -fvc::grad( p ) );
  }
  else
  {
    U = rAU() * ( UEqn->H() - fvc::grad( p() ) );
    U->correctBoundaryConditions();
  }
  
  return UEqn;
}
//---------------------------------------------------------------------------
void fun_hEqn( const basicPsiThermoHolder& thermo,
               const volScalarFieldHolder& rho,
               const volScalarFieldHolder& p,
               const volScalarFieldHolder& h,
               const surfaceScalarFieldHolder& phi,
               const compressible::turbulenceModelHolder& turbulence,
               const volScalarFieldHolder& DpDt )
{
  smart_tmp< fvScalarMatrix > hEqn( fvm::ddt( rho(), h() ) + fvm::div( phi(), h () )- fvm::laplacian( turbulence->alphaEff(), h() )
                                    == DpDt() );

  hEqn->relax();
  hEqn->solve();

  thermo->correct();

}


//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               const pimpleControlHolder& pimple,
               basicPsiThermoHolder& thermo,
               volScalarFieldHolder& rho,
               volScalarFieldHolder& p,
               volScalarFieldHolder& h,
               volScalarFieldHolder& psi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& phi,
               compressible::turbulenceModelHolder& turbulence,
               fvVectorMatrixHolder& UEqn,
               MRFZonesHolder& mrfZones,
               volScalarFieldHolder& DpDt,
               scalar& cumulativeContErr,
               int& corr,
               dimensionedScalar& rhoMax,
               dimensionedScalar& rhoMin )
{
  rho = thermo->rho();
  rho = max( rho(), rhoMin );
  rho = min( rho(), rhoMax );
  rho->relax();

  smart_tmp< volScalarField >  rAU( 1.0 / UEqn->A() );
  U = rAU() * UEqn->H();

  if (pimple->nCorr() <= 1)
  {
    //UEqn->clear();
  }

  if (pimple->transonic())
  {
     surfaceScalarField phid( "phid", fvc::interpolate( psi() ) * ( ( fvc::interpolate( U() ) & mesh->Sf() )
                                                                    + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) ) );

    mrfZones->relativeFlux( fvc::interpolate( psi() ), phid);
    
    for (int nonOrth=0; nonOrth <= pimple->nNonOrthCorr(); nonOrth++ )
    {
      smart_tmp< fvScalarMatrix > pEqn( fvm::ddt( psi(), p() ) + fvm::div( phid, p() ) - fvm::laplacian( rho() * rAU(), p() ) );

      pEqn->solve( mesh->solver( p->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );

      if ( nonOrth == pimple->nNonOrthCorr() )
      {
        phi == pEqn->flux();
      }
    }
  }
  else
  {
    phi = fvc::interpolate( rho() ) * ( ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) );
    
    mrfZones->relativeFlux( fvc::interpolate( rho() ), phi() );

    for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
    {
      // Pressure corrector
      smart_tmp< fvScalarMatrix > pEqn( fvm::ddt( psi(), p() ) + fvc::div( phi() ) - fvm::laplacian( rho()*rAU(), p() ) );

      pEqn->solve( mesh->solver( p->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );

      if ( nonOrth == pimple->nNonOrthCorr() )
      {
        phi += pEqn->flux();
      }
    }
  }

  rhoEqn( rho, phi );
  compressibleContinuityErrs( thermo, rho, cumulativeContErr );

  // Explicitly relax pressure for momentum corrector
  p->relax();

  // Recalculate density from the relaxed pressure
  rho = thermo->rho();
  rho = max( rho(), rhoMin );
  rho = min( rho(), rhoMax );
  rho->relax();
  Info<< "rho max/min : " << max( rho() ).value()  << " " << min( rho() ).value() << endl;

  U -= rAU() * fvc::grad( p() );
  U->correctBoundaryConditions();

  DpDt = fvc::DDt(surfaceScalarField("phiU", phi() / fvc::interpolate( rho() ) ), p());
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  basicPsiThermoHolder pThermo; volScalarFieldHolder rho; volScalarFieldHolder p;
  volScalarFieldHolder h; volScalarFieldHolder psi;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  compressible::turbulenceModelHolder turbulence; 
  volScalarFieldHolder DpDt;
  
  result_createFields result = createFields( runTime, mesh, pThermo, rho, p, h, psi, U,  phi, turbulence, DpDt );
  dimensionedScalar rhoMax = result.m_rhoMax;
  dimensionedScalar rhoMin = result.m_rhoMin;

  MRFZonesHolder mrfZones;
  porousZonesHolder pZones;
  Switch pressureImplicitPorosity;
  
  createZones( mesh, U, mrfZones, pZones, pressureImplicitPorosity );

  scalar cumulativeContErr = initContinuityErrs();
  
  pimpleControlHolder pimple(mesh);

  Info<< "\nStarting time loop\n" << endl;

  while (runTime->run())
  {
    bool adjustTimeStep; scalar maxCo; scalar maxDeltaT;
    readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );

    scalar coNum, meanCoNum;
    compressibleCourantNo( runTime, mesh, phi, rho, coNum, meanCoNum );

    setDeltaT( runTime, adjustTimeStep, maxCo, coNum, maxDeltaT );
    (*runTime)++;

    Info<< "Time = " << runTime->timeName() << nl << endl;

    rhoEqn( rho, phi );

    // --- Pressure-velocity PIMPLE corrector loop
    for (pimple->start(); pimple->loop(); (*pimple)++)
    {
      if (pimple->nOuterCorr() != 1)
      {
        p->storePrevIter();
        rho->storePrevIter();
      }

      fvVectorMatrixHolder UEqn = fun_Ueqn( pimple, rho, p, U, phi, turbulence, mrfZones, pZones );
      
      fun_hEqn( pThermo, rho, p, h, phi, turbulence, DpDt );
      
      // --- PISO loop
      for (int corr=0; corr<pimple->nCorr(); corr++)
      {
        fun_pEqn( mesh, runTime, pimple, pThermo, rho, p, h, psi, U, phi, turbulence, UEqn,
                  mrfZones, DpDt, cumulativeContErr, corr, rhoMax, rhoMin );
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
