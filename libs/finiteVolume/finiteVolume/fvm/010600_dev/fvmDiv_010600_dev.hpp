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
#ifndef fvmDiv_010600_dev_hpp
#define fvmDiv_010600_dev_hpp


//---------------------------------------------------------------------------
#include <fvmDiv.H>
#include "volFields.hpp"
#include "surfaceFields.hpp"
#include "fvMatrices.hpp"

//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    template< class Type >
    inline fvMatrixHolder< Type > div( const surfaceScalarFieldHolder& field1,
                                       GeometricFieldHolder< Type, fvPatchField, volMesh >& field2 )
    {
      return fvMatrixHolder< Type >( div( field1(), field2() ), Deps( &field1, &field2 ) );
    }
   
  } // fvm
} //Foam


//---------------------------------------------------------------------------
#endif

