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
#ifndef fvcSurfaceIntegrate_hpp
#define fvcSurfaceIntegrate_hpp


//---------------------------------------------------------------------------
#include <fvcSurfaceIntegrate.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
   template<class Type>
   inline GeometricFieldHolder< Type, fvPatchField, volMesh> surfaceSum( const GeometricFieldHolder< Type, fvsPatchField, surfaceMesh >& field1 )
    
   {
     return GeometricFieldHolder< Type, fvPatchField, volMesh >( surfaceSum( field1() ), Deps( field1.deps() ) );
   }
   
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
