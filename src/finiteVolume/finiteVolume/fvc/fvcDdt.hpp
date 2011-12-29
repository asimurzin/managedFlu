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
#ifndef fvcDdt_hpp
#define fvcDdt_hpp


//---------------------------------------------------------------------------
#include <fvcDdt.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    template<class Type>
    GeometricFieldHolder< Type, fvPatchField, volMesh> ddt( const dimensioned<Type> dt, const fvMeshHolder& mesh )
    {
      return GeometricFieldHolder< Type, fvPatchField, volMesh >( ddt( dt, *mesh ), Deps( &mesh ) );
    }

    template<class Type>
    GeometricFieldHolder< Type, fvPatchField, volMesh> ddt( const GeometricFieldHolder<Type, fvPatchField, volMesh>& field )
    {
      return GeometricFieldHolder< Type, fvPatchField, volMesh >( ddt( field() ), Deps( field.deps() ) );
    }

    template<class Type>
    GeometricFieldHolder< Type, fvPatchField, volMesh > ddt( const dimensionedScalar& dS,  const GeometricFieldHolder<Type, fvPatchField, volMesh>& field )
    {
      return GeometricFieldHolder< Type, fvPatchField, volMesh >( ddt( dS, field() ), Deps( field.deps() ) );
    }

    template<class Type>
    GeometricFieldHolder< Type, fvPatchField, volMesh > ddt( const volScalarFieldHolder& field1, const GeometricFieldHolder<Type, fvPatchField, volMesh>& field2 )
    {
      return GeometricFieldHolder< Type, fvPatchField, volMesh >( ddt( field1(), field2() ), Deps( field1.deps(), field2.deps() ) );
    }
   
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
