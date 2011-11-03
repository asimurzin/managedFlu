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
    buoyantPimpleFoam

Description
    Transient solver for buoyant, turbulent flow of compressible fluids for
    ventilation and heat-transfer.

    Turbulence is modelled using a run-time selectable compressible RAS or
    LES model.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fixedGradientFvPatchFields.H"
#include "pimpleControl.H"

#include "core.hpp"
#include "pimpleControlHolder.hpp"
#include "basicRhoThermoHolder.hpp"
#include "turbulenceModels/compressible/turbulenceModel/turbulenceModelHolder.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "compressibleContinuityErrs.hpp"
#include "compressibleCreatePhi.hpp"
#include "compressibleCourantNo.hpp"
#include "rhoEqn.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
void createFields( const TimeHolder& runTime, const fvMeshHolder& mesh, const uniformDimensionedVectorFieldHolder& g,
                   basicRhoThermoHolder& pThermo, volScalarFieldHolder& rho,
                   volScalarFieldHolder& p, volScalarFieldHolder& h,
                   volScalarFieldHolder& psi, volVectorFieldHolder& U,
                   surfaceScalarFieldHolder& phi, compressible::turbulenceModelHolder& turbulence,
                   volScalarFieldHolder& gh, surfaceScalarFieldHolder& ghf,
                   volScalarFieldHolder& p_rgh, volScalarFieldHolder& DpDt  )
{
  Info<< "Reading thermophysical properties\n" << endl;

  pThermo = basicRhoThermoHolder::New( mesh );

  rho( volScalarFieldHolder( IOobjectHolder( "rho", 
                                            runTime->timeName(),
                                            mesh, 
                                            IOobject::NO_READ, 
                                            IOobject::NO_WRITE ),
                              volScalarFieldHolder( pThermo->rho(), Deps( &pThermo ) ) ) );

  p( volScalarFieldHolder( pThermo->p(), Deps( &pThermo ) ) );
  h( volScalarFieldHolder( pThermo->h(), Deps( &pThermo ) ) );
  psi( volScalarFieldHolder( pThermo->psi(), Deps( &pThermo ) ) );
  

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                          runTime->timeName(),
                                          mesh,
                                          IOobject::MUST_READ,
                                          IOobject::AUTO_WRITE ),
                          mesh ) );


  phi( compressibleCreatePhi( runTime, mesh, U, rho ) );


  Info<< "Creating turbulence model\n" << endl;
  turbulence = compressible::turbulenceModelHolder::New( rho, U, phi, pThermo );

  Info<< "Calculating field g.h\n" << endl;
  gh( volScalarFieldHolder("gh", g & volVectorFieldHolder( mesh->C(), Deps( &mesh ) ) ) );
  ghf( surfaceScalarFieldHolder("ghf", g & surfaceVectorFieldHolder( mesh->Cf(), Deps( &mesh ) ) ) );

  Info<< "Reading field p_rgh\n" << endl;
  p_rgh( volScalarFieldHolder( IOobjectHolder( "p_rgh",
                                                runTime->timeName(),
                                                mesh,
                                                IOobject::MUST_READ,
                                                IOobject::AUTO_WRITE ),
                                mesh ) );

  // Force p_rgh to be consistent with p
  p_rgh = p - rho*gh;

  Info<< "Creating field DpDt\n" << endl;
  DpDt( volScalarFieldHolder( "DpDt", 
                              fvc::DDt( surfaceScalarFieldHolder( "phiU", phi / fvc::interpolate( rho ) ), p ) ) );
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_Ueqn( const pimpleControlHolder& pimple,
                              const fvMeshHolder& mesh,
                              const volScalarFieldHolder& rho,
                              volVectorFieldHolder& U, 
                              const surfaceScalarFieldHolder& phi, 
                              const compressible::turbulenceModelHolder& turbulence,
                              const surfaceScalarFieldHolder& ghf,
                              const volScalarFieldHolder& p_rgh )
{
  // Solve the Momentum equation

  fvVectorMatrixHolder UEqn( fvm::ddt( rho, U ) + fvm::div( phi, U ) + fvVectorMatrixHolder( turbulence->divDevRhoReff( U() ), Deps( &turbulence, &U ) ) );
  
  UEqn->relax();

  if ( pimple->momentumPredictor() )
  {
    solve( UEqn == fvc::reconstruct(  ( - ghf * fvc::snGrad( rho ) - fvc::snGrad( p_rgh ) ) * surfaceScalarFieldHolder( mesh->magSf(), Deps( &mesh ) ) ) );
  }
  
  return UEqn;
}


//---------------------------------------------------------------------------
void fun_hEqn( const basicRhoThermoHolder& thermo,
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
               basicRhoThermoHolder& thermo,
               volScalarFieldHolder& rho,
               volScalarFieldHolder& p,
               volScalarFieldHolder& h,
               volScalarFieldHolder& psi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& phi,
               compressible::turbulenceModelHolder& turbulence,
               volScalarFieldHolder& gh,
               surfaceScalarFieldHolder& ghf,
               volScalarFieldHolder& p_rgh,
               fvVectorMatrixHolder& UEqn,
               volScalarFieldHolder& DpDt,
               scalar& cumulativeContErr,
               int& corr )
{
  rho = thermo->rho();
  
  // Thermodynamic density needs to be updated by psi*d(p) after the
  // pressure solution - done in 2 parts. Part 1:
  thermo->rho() -= psi() * p_rgh();
  
  smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );
  surfaceScalarField rhorAUf("(rho*(1|A(U)))", fvc::interpolate( rho() * rAU() ) );
  

  U = rAU() * UEqn->H();

  phi = fvc::interpolate( rho() ) * ( ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), rho(), U(), phi() ) );

  smart_tmp< surfaceScalarField > buoyancyPhi( -rhorAUf * ghf() * fvc::snGrad( rho() ) * mesh->magSf() );
  
  phi += buoyancyPhi;

  smart_tmp< fvScalarMatrix > p_rghDDtEqn( fvc::ddt( rho() ) + psi() * correction( fvm::ddt( p_rgh() ) ) + fvc::div( phi() ) );

  for (int nonOrth=0; nonOrth <= pimple->nNonOrthCorr(); nonOrth++)
  {
    smart_tmp< fvScalarMatrix > p_rghEqn( p_rghDDtEqn() - fvm::laplacian( rhorAUf, p_rgh() ) );

    p_rghEqn->solve( mesh->solver( p_rgh->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );
    
    if ( nonOrth == pimple->nNonOrthCorr() )
    {
      // Calculate the conservative fluxes
      phi += p_rghEqn->flux();
 
      // Explicitly relax pressure for momentum corrector
      p_rgh->relax();
 
      // Correct the momentum source with the pressure gradient flux
      // calculated from the relaxed pressure
      U += rAU() * fvc::reconstruct( ( buoyancyPhi() + p_rghEqn->flux() ) / rhorAUf );
      U->correctBoundaryConditions();
    }
  }

  p = p_rgh + rho*gh;

  // Second part of thermodynamic density update
  thermo->rho() += psi() * p_rgh();

  DpDt = fvc::DDt(surfaceScalarField("phiU", phi() / fvc::interpolate( rho() ) ), p() );

  rhoEqn( rho, phi );
  compressibleContinuityErrs( thermo, rho, cumulativeContErr );
  
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  uniformDimensionedVectorFieldHolder g = readGravitationalAcceleration( runTime, mesh );
  
  basicRhoThermoHolder pThermo; volScalarFieldHolder rho; volScalarFieldHolder p;
  volScalarFieldHolder h; volScalarFieldHolder psi;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  compressible::turbulenceModelHolder turbulence; volScalarFieldHolder gh;
  surfaceScalarFieldHolder ghf; volScalarFieldHolder p_rgh; 
  volScalarFieldHolder DpDt;
  
  createFields( runTime, mesh, g, pThermo, rho, p, h, psi, U,  phi, turbulence, gh, ghf, p_rgh, DpDt );

  scalar cumulativeContErr = initContinuityErrs();
  
  bool adjustTimeStep; scalar maxCo; scalar maxDeltaT;
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
  
  scalar coNum, meanCoNum;
  compressibleCourantNo( runTime, mesh, phi, rho, coNum, meanCoNum );
  
  setInitialDeltaT( runTime, adjustTimeStep, maxCo, coNum );
  
  pimpleControlHolder pimple(mesh);

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;

  while ( runTime->run() )
  {
    readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
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
        p_rgh->storePrevIter();
      }
      
      fvVectorMatrixHolder UEqn = fun_Ueqn( pimple, mesh, rho, U, phi, turbulence, ghf, p_rgh );
      fun_hEqn( pThermo, rho, p, h, phi, turbulence, DpDt );
      
      // --- PISO loop
      for (int corr=0; corr<pimple->nCorr(); corr++)
      {
        fun_pEqn( mesh, runTime, pimple, pThermo, rho, p, h, psi, U, phi, turbulence, gh, ghf, p_rgh, UEqn, DpDt, cumulativeContErr, corr );
      }

      if (pimple->turbCorr())
      {
        turbulence->correct();
      }

    }

    rho = pThermo->rho();

    runTime->write();

    Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
