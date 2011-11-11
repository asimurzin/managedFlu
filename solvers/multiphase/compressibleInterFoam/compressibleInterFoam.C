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
    compressibleInterFoam

Description
    Solver for 2 compressible, isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

    Turbulence modelling is generic, i.e.  laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "MULES.H"
#include "subCycle.H"
#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "interfacePropertiesHolder.hpp"
#include "twoPhaseMixtureHolder.hpp"
#include "turbulenceModelHolder.hpp"
#include "pimpleControlHolder.hpp"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  uniformDimensionedVectorFieldHolder g = readGravitationalAcceleration( runTime, mesh );

  Info<< "Reading field p_rgh\n" << endl;
  volScalarFieldHolder p_rgh( IOobjectHolder( "p_rgh",
                                               runTime->timeName(),
                                               mesh,
                                               IOobject::MUST_READ,
                                               IOobject::AUTO_WRITE ),
                               mesh );
  Info<< "Reading field alpha1\n" << endl;
  volScalarFieldHolder alpha1( IOobjectHolder( "alpha1",
                                                runTime->timeName(),
                                                mesh,
                                                IOobject::MUST_READ,
                                                IOobject::AUTO_WRITE ),
                                mesh );

  Info<< "Calculating field alpha1\n" << endl;
  volScalarFieldHolder alpha2( "alpha2", scalar( 1 ) - alpha1 );
  
  
  Info<< "Reading field U\n" << endl;
  volVectorFieldHolder U( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh );
  Info<< "Reading field phi\n" << endl;
  surfaceScalarFieldHolder phi( createPhi( runTime, mesh, U ) );
  
  Info<< "Reading transportProperties\n" << endl;
  twoPhaseMixtureHolder twoPhaseProperties(U, phi);

  dimensionedScalar rho10( twoPhaseProperties->subDict( twoPhaseProperties->phase1Name() ).lookup( "rho0" ) );
  dimensionedScalar rho20( twoPhaseProperties->subDict( twoPhaseProperties->phase2Name() ).lookup( "rho0" ) );
  dimensionedScalar psi1( twoPhaseProperties->subDict( twoPhaseProperties->phase1Name() ).lookup( "psi" ) );
  dimensionedScalar psi2( twoPhaseProperties->subDict( twoPhaseProperties->phase2Name() ).lookup( "psi" ) );
  dimensionedScalar pMin(twoPhaseProperties->lookup("pMin"));

  Info<< "Calculating field g.h\n" << endl;
  volScalarFieldHolder gh("gh", g & volVectorFieldHolder( mesh->C(), Deps( &mesh ) ) );
  Info<< "Reading field ghf\n" << endl;
  surfaceScalarFieldHolder ghf( "ghf", g & surfaceVectorFieldHolder( mesh->Cf(), Deps( &mesh ) ) );
  Info<< "Reading field p\n" << endl;
  volScalarFieldHolder temp( ( p_rgh + gh * ( alpha1 * rho10 + alpha2 * rho20) ) / 
                                ( 1.0 - gh * ( alpha1 * psi1 + alpha2 * psi2) ) );

  volScalarFieldHolder p( IOobjectHolder( "p",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::NO_READ,
                                           IOobject::AUTO_WRITE ),
                           temp );
  Info<< "Reading field rho\n" << endl;
  volScalarFieldHolder rho( IOobjectHolder( "rho",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::READ_IF_PRESENT,
                                             IOobject::AUTO_WRITE ),
                             alpha1 );


  // tmp<fvScalarMatrix> p_rghEqnComp = ( fvm::ddt(p_rgh() ) + fvc::div( phi(), p_rgh() ) - fvc::Sp( fvc::div( phi() ), p_rgh() ) );
  
  tmp<fvScalarMatrix> p_rghEqnComp = fvm::ddt(p_rgh() );
  
  p_rghEqnComp & p_rgh();
  
  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
