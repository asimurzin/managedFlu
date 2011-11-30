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
#ifndef fvmDdt_020000_hpp
#define fvmDdt_020000_hpp


//---------------------------------------------------------------------------
#include <fvmDdt.H>
#include "volFields.hpp"
#include "surfaceFields.hpp"
#include "fvMatrices.hpp"

//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    template< class Type >
    inline fvMatrixHolder< Type > ddt( const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
    {
      return fvMatrixHolder<Type>( ddt( field() ), &field );
    }
    
    template< class Type >
    inline fvMatrixHolder< Type > ddt( const volScalarFieldHolder& field1,
                                       const GeometricFieldHolder< Type, fvPatchField, volMesh >& field2 )
    {
      return fvMatrixHolder<Type>( ddt( field1(), field2() ),  Deps( &field1, &field2 ) );
    }
   
  } // fvm
} //Foam


//---------------------------------------------------------------------------
#endif

