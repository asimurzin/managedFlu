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
//#include "Allfunctions.hpp"
#include "thermophysicalModels.hpp"
#include "turbulenceModels.hpp"



//---------------------------------------------------------------------------
volScalarFieldHolder createFields( const Foam::word& dict_name, const Foam::argList& args )
{
  TimeHolder runTime( dict_name, args);
  
  fvMeshHolder mesh( IOobjectHolder( fvMesh::defaultRegion,
				     runTime->timeName(),
			             runTime,
				     IOobject::MUST_READ ) );
  
  Info<< "Reading thermophysical properties\n" << endl;

  basicPsiThermoHolder pThermo = basicPsiThermoHolder::New( mesh );

  tmp< volScalarField > rho1( new volScalarField( ( IOobject( "rho", 
                                                              runTime->timeName(),
                                                              *mesh, 
                                                              IOobject::NO_READ, 
                                                              IOobject::NO_WRITE ),
                                                    pThermo->rho() ) ) );

  volScalarFieldHolder rho( rho1, universalArgs( &pThermo ) );
                                               
   return rho;

}

int main(int argc, char *argv[])
{
  Foam::argList args(argc, argv);
   
  volScalarFieldHolder rho = createFields( Foam::Time::controlDictName, args );

  return 0;
}


// ************************************************************************* //
