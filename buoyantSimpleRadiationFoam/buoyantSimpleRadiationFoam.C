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



//---------------------------------------------------------------------------
/*struct result_createFields
{
  dimensionedScalar m_initialMass;
  dimensionedScalar m_totalVolume;
  result_createFields( dimensionedScalar the_initialMass, dimensionedScalar the_totalVolume )
    : m_initialMass( the_initialMass )
    , m_totalVolume( the_totalVolume )
  {}
};*/


//---------------------------------------------------------------------------
void createFields( const TimeHolder& runTime, const fvMeshHolder& mesh )
{
  Info<< "Reading thermophysical properties\n" << endl;

  basicPsiThermoHolder pThermo = basicPsiThermoHolder::New( mesh );

  volScalarFieldHolder rho( IOobjectHolder( "rho", 
                                            runTime->timeName(),
                                            mesh, 
                                            IOobject::NO_READ, 
                                            IOobject::NO_WRITE ),
                            pThermo->rho() );

  volScalarFieldHolder p = pThermo->p();
  volScalarFieldHolder h = pThermo->h();
  const volScalarFieldHolder psi = pThermo->psi();
  

  Info<< "Reading field U\n" << endl;
  volVectorField Ux( IOobject( "U",
                                          runTime->timeName(),
                                          *mesh,
                                          IOobject::MUST_READ,
                                          IOobject::AUTO_WRITE ),
                          *mesh );

  volVectorFieldHolder U( Ux );
  
  surfaceScalarFieldHolder phi = compressibleCreatePhi( runTime, mesh, U, rho );


    Info<< "Creating turbulence model\n" << endl;
    compressible::RASModelHolder turbulence = compressible::RASModelHolder::New(
      rho,
      U,
      phi,
      pThermo );

/*
    Info<< "Calculating field g.h\n" << endl;
    volScalarField gh("gh", g & mesh.C());
    surfaceScalarField ghf("ghf", g & mesh.Cf());

    Info<< "Reading field p_rgh\n" << endl;
    volScalarField p_rgh
    (
        IOobject
        (
            "p_rgh",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    // Force p_rgh to be consistent with p
    p_rgh = p - rho*gh;


    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell
    (
        p,
        p_rgh,
        mesh.solutionDict().subDict("SIMPLE"),
        pRefCell,
        pRefValue
    );

    dimensionedScalar initialMass = fvc::domainIntegrate(rho);
    dimensionedScalar totalVolume = sum(mesh.V());*/
}

int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  uniformDimensionedVectorField g = readGravitationalAcceleration( runTime, mesh );
  
  createFields( runTime, mesh );
  

    
/*    #include "createFields.H"
    #include "createRadiationModel.H"
    #include "initContinuityErrs.H"

    simpleControl simple(mesh);

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (simple.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        p_rgh.storePrevIter();
        rho.storePrevIter();

        // Pressure-velocity SIMPLE corrector
        {
            #include "UEqn.H"
            #include "hEqn.H"
            #include "pEqn.H"
        }

        turbulence->correct();

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;*/
}


// ************************************************************************* //
