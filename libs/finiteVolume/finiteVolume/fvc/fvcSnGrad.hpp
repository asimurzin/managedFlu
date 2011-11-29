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
#ifndef fvcSnGrad_hpp
#define fvcSnGrad_hpp


//---------------------------------------------------------------------------
#include <fvcSnGrad.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
   template<class Type>
   inline GeometricFieldHolder< Type, fvsPatchField, surfaceMesh > snGrad( const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
    
   {
     return GeometricFieldHolder< Type, fvsPatchField, surfaceMesh >( snGrad( field() ), Deps( field.deps() ) );
   }
   
   template<class Type>
   inline GeometricFieldHolder<  Type, fvsPatchField, surfaceMesh > snGrad( const GeometricFieldHolder< Type, fvPatchField, volMesh >& field,
                                                                     const word& name )
    
   {
     return GeometricFieldHolder< Type, fvsPatchField, surfaceMesh >( snGrad( field(), name ), Deps( field.deps() ) );
   }

  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
