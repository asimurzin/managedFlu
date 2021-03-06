//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2011- Alexey Petrov
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  See http://sourceforge.net/projects/pythonflu
//
//  Author : Alexey PETROV, Andrey Simurzin


//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
void compressibleCourantNo( 
  const TimeHolder& runTime, 
  const fvMeshHolder& mesh, 
  const surfaceScalarFieldHolder& phi,
  const volScalarFieldHolder& rho,
  scalar& CoNum,
  scalar& meanCoNum )
{
  CoNum = 0.0;
  meanCoNum = 0.0;

  if ( mesh->nInternalFaces() )
  {
    scalarField sumPhi( fvc::surfaceSum( mag( phi ) )().internalField() / rho->internalField() );

    CoNum = 0.5 * gMax( sumPhi / mesh->V().field() ) * runTime->deltaTValue();

    meanCoNum = 0.5 * ( gSum( sumPhi ) / gSum( mesh->V().field() ) )*runTime->deltaTValue();
  }

  Info<< "Courant Number mean: " << meanCoNum
      << " max: " << CoNum << endl;
}


//---------------------------------------------------------------------------

