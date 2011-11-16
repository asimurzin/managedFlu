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
  volScalarField::debug = 1;
  //fv::debug = 1;
  //fvScalarMatrix::debug = 1;
  
  DimensionedField<scalar, volMesh>::debug = 1;
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

  Info<< "Reading field rho\n" << endl;
  volScalarFieldHolder rho( IOobjectHolder( "rho",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::READ_IF_PRESENT,
                                             IOobject::AUTO_WRITE ),
                            p_rgh );

  Info<< "matrix & p_rgh\n \n\n" << endl;
  int ref_count = p_rgh->count();
  Info << p_rgh->count() << nl;
  fvm::ddt( p_rgh() ) & p_rgh();
  for( int i=0; i<ref_count; i++ )
  {
    p_rgh->operator++();
  }
  Info << p_rgh->count() << nl;
  
  //Info << p_rgh() * 2 << endl;
  
  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
