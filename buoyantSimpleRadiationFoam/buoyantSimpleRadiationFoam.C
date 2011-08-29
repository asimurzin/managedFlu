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
    buoyantSimpleRadiationFoam

Description
    Steady-state solver for buoyant, turbulent flow of compressible fluids,
    including radiation, for ventilation and heat-transfer.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "basicPsiThermo.H"
#include "RASModel.H"
#include "fixedGradientFvPatchFields.H"
#include "radiationModel.H"
#include "simpleControl.H"
#include "core.hpp"
#include "Allfunctions.hpp"
#include "thermophysicalModels.hpp"
#include "turbulenceModels.hpp"
#include "radiationModels.hpp"



//---------------------------------------------------------------------------
struct result_createFields
{
  dimensionedScalar m_initialMass;
  dimensionedScalar m_totalVolume;
  result_createFields( dimensionedScalar the_initialMass, dimensionedScalar the_totalVolume )
    : m_initialMass( the_initialMass )
    , m_totalVolume( the_totalVolume )
  {}
};


//---------------------------------------------------------------------------
result_createFields createFields( const TimeHolder& runTime, const fvMeshHolder& mesh, const uniformDimensionedVectorField& g,
                                   basicPsiThermoHolder& pThermo,
                                   volScalarFieldHolder& rho,
                                   volScalarFieldHolder& p,
                                   volScalarFieldHolder& h,
                                   volScalarFieldHolder& psi,
                                   volVectorFieldHolder& U,
                                   surfaceScalarFieldHolder& phi,
                                   compressible::RASModelHolder& turbulence,
                                   volScalarFieldHolder& gh,
                                   surfaceScalarFieldHolder& ghf,
                                   volScalarFieldHolder& p_rgh,
                                   label& pRefCell,
                                   scalar& pRefValue )
{
  Info<< "Reading thermophysical properties\n" << endl;

  pThermo = basicPsiThermoHolder::New( mesh );

  rho = volScalarFieldHolder( IOobjectHolder( "rho", 
                                            runTime->timeName(),
                                            mesh, 
                                            IOobject::NO_READ, 
                                            IOobject::NO_WRITE ),
                            volScalarFieldHolder( pThermo->rho(),&pThermo ) );

  p = volScalarFieldHolder( pThermo->p(), &pThermo );
  h = volScalarFieldHolder( pThermo->h(), &pThermo );
  psi = volScalarFieldHolder( pThermo->psi(), &pThermo );
  

  Info<< "Reading field U\n" << endl;
  U = volVectorFieldHolder( IOobjectHolder( "U",
                                          runTime->timeName(),
                                          mesh,
                                          IOobject::MUST_READ,
                                          IOobject::AUTO_WRITE ),
                          mesh );


  phi = compressibleCreatePhi( runTime, mesh, U, rho );


  Info<< "Creating turbulence model\n" << endl;
  turbulence = compressible::RASModelHolder::New( rho,
                                                  U,
                                                  phi,
                                                  pThermo );


  Info<< "Calculating field g.h\n" << endl;
    
  gh = volScalarFieldHolder("gh", g & volVectorFieldHolder( mesh->C(), &mesh ) );
  ghf = surfaceScalarFieldHolder("ghf", g & surfaceVectorFieldHolder( mesh->Cf(), &mesh ) );
  
  Info<< "Reading field p_rgh\n" << endl;
  p_rgh = volScalarFieldHolder( IOobjectHolder( "p_rgh",
                                                runTime->timeName(),
                                                mesh,
                                                IOobject::MUST_READ,
                                                IOobject::AUTO_WRITE ),
                                mesh );

  // Force p_rgh to be consistent with p
  p_rgh = p() - rho()*gh();

  pRefCell = 0;
  pRefValue = 0.0;
  setRefCell( p, p_rgh, mesh->solutionDict().subDict("SIMPLE"), pRefCell, pRefValue );

  return result_createFields( fvc::domainIntegrate( rho() ), sum( mesh->V() ) );
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_Ueqn( const simpleControlHolder& simple,
                              const fvMeshHolder& mesh,
                              const volScalarFieldHolder& rho,
                              volVectorFieldHolder& U, 
                              const surfaceScalarFieldHolder& phi, 
                              const compressible::RASModelHolder& turbulence,
                              const surfaceScalarFieldHolder& ghf,
                              const volScalarFieldHolder& p_rgh )
{
  // Solve the Momentum equation

  fvVectorMatrixHolder UEqn = fvm::div(phi, U) + fvVectorMatrixHolder( turbulence->divDevRhoReff( U() ), &turbulence ); // turbulence && U

  UEqn->relax();
 
  if ( simple->momentumPredictor() )
     solve( UEqn == fvc::reconstruct( ( ( - ghf*fvc::snGrad(rho) - fvc::snGrad(p_rgh) ) * surfaceScalarFieldHolder( mesh->magSf(), &mesh ) ) ) );

  return UEqn;

}


//---------------------------------------------------------------------------
void fun_hEqn( const basicPsiThermoHolder& thermo,
               const volScalarFieldHolder& rho,
               const volScalarFieldHolder& p,
               const volScalarFieldHolder& h,
               const surfaceScalarFieldHolder& phi,
               const radiation::radiationModelHolder& radiation, 
               const compressible::RASModelHolder& turbulence )
{
  fvScalarMatrix hEqn
    (
        fvm::div( phi(), h() )
      - fvm::Sp(fvc::div( phi() ), h() )
      - fvm::laplacian(turbulence->alphaEff(), h() )
     ==
        fvc::div( phi() / fvc::interpolate( rho() ) * fvc::interpolate( p() ) )
      - p() * fvc::div( phi() / fvc::interpolate( rho() ))
      + radiation->Sh( *thermo )
    );

    hEqn.relax();

    hEqn.solve();

    thermo->correct();

    radiation->correct();
}


//---------------------------------------------------------------------------
void fun_pEqn( const fvMeshHolder& mesh,
               const TimeHolder& runTime,
               const simpleControlHolder& simple,
               basicPsiThermoHolder& thermo,
               volScalarFieldHolder& rho,
               volScalarFieldHolder& p,
               volScalarFieldHolder& h,
               volScalarFieldHolder& psi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& phi,
               compressible::RASModelHolder& turbulence,
               volScalarFieldHolder& gh,
               surfaceScalarFieldHolder& ghf,
               volScalarFieldHolder& p_rgh,
               fvVectorMatrixHolder& UEqn,
               label& pRefCell,
               scalar& pRefValue,
               scalar& cumulativeContErr, 
               dimensionedScalar& initialMass)
{
  rho = thermo->rho();
  rho->relax();

  volScalarField rAU(1.0/UEqn->A());
  
  surfaceScalarField rhorAUf( "(rho*(1|A(U)))", fvc::interpolate( rho()*rAU ) );

  U = rAU * UEqn->H();
  //UEqn.clear();

  phi = fvc::interpolate( rho() ) * ( fvc::interpolate( U() ) & mesh->Sf());
  bool closedVolume = adjustPhi(phi, U, p_rgh);
  surfaceScalarField buoyancyPhi( rhorAUf * ghf() * fvc::snGrad( rho() ) * mesh->magSf() );
  phi -= buoyancyPhi;

  for (int nonOrth=0; nonOrth<= simple->nNonOrthCorr(); nonOrth++)
  {
    fvScalarMatrix p_rghEqn
        (
            fvm::laplacian( rhorAUf, p_rgh() ) == fvc::div( phi() )
        );

        p_rghEqn.setReference( pRefCell, getRefCellValue( p_rgh(), pRefCell ) );
        p_rghEqn.solve();

        if (nonOrth == simple->nNonOrthCorr())
        {
            // Calculate the conservative fluxes
            phi -= p_rghEqn.flux();

            // Explicitly relax pressure for momentum corrector
            p_rgh->relax();

            // Correct the momentum source with the pressure gradient flux
            // calculated from the relaxed pressure
            U -= rAU * fvc::reconstruct( ( buoyancyPhi + p_rghEqn.flux() ) / rhorAUf );
            U->correctBoundaryConditions();
        }
    }

    continuityErrors( runTime, mesh, phi, cumulativeContErr );

    p = p_rgh() + rho() * gh();

    // For closed-volume cases adjust the pressure level
    // to obey overall mass continuity
    if (closedVolume)
    {
        dimensionedScalar xx = ( initialMass - fvc::domainIntegrate( psi() * p() ) ) / fvc::domainIntegrate( psi() );
        p += ( initialMass - fvc::domainIntegrate( psi() * p() ) ) / fvc::domainIntegrate( psi() );
        p_rgh = p() - rho() * gh();
    }

    rho = thermo->rho();
    rho->relax();
    Info<< "rho max/min : " << max( rho() ).value() << " " << min( rho() ).value()
        << endl;
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  uniformDimensionedVectorField g = readGravitationalAcceleration( runTime, mesh );
  
  basicPsiThermoHolder pThermo; volScalarFieldHolder rho; volScalarFieldHolder p;
  volScalarFieldHolder h; volScalarFieldHolder psi;
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  compressible::RASModelHolder turbulence; volScalarFieldHolder gh;
  surfaceScalarFieldHolder ghf; volScalarFieldHolder p_rgh; 
  label pRefCell; scalar pRefValue;
  
  result_createFields result = createFields( runTime, mesh, g, pThermo, rho, p,
                                             h, psi, U,  phi, turbulence, gh, ghf, p_rgh, pRefCell, pRefValue );
  
  
  dimensionedScalar initialMass = result.m_initialMass;
  dimensionedScalar totalVolume = result.m_totalVolume;
 
  radiation::radiationModelHolder radiation = createRadiationModel( pThermo );
  
  scalar cumulativeContErr = initContinuityErrs();
  
  simpleControlHolder simple( mesh );
  simple->nNonOrthCorr();
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;

    while (simple->loop())
    {
        Info<< "Time = " << runTime->timeName() << nl << endl;

        p_rgh->storePrevIter();
        rho->storePrevIter();
        
        // Pressure-velocity SIMPLE corrector
        {
            fvVectorMatrixHolder UEqn = fun_Ueqn( simple, mesh, rho, U, phi, turbulence, ghf, p_rgh );
            fun_hEqn( pThermo, rho, p, h, phi, radiation, turbulence );
          /*#include "pEqn.H"*/
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
