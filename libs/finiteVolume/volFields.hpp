//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
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
#ifndef volFields_hpp
#define volFields_hpp


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.hpp"

#include <volFields.H>


//---------------------------------------------------------------------------
namespace Foam
{
  typedef GeometricFieldHolder< scalar, fvPatchField, volMesh > volScalarFieldHolder;
  typedef GeometricFieldHolder< vector, fvPatchField, volMesh > volVectorFieldHolder;
  typedef GeometricFieldHolder< tensor, fvPatchField, volMesh > volTensorFieldHolder;
}

//---------------------------------------------------------------------------
#endif
