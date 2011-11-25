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
#ifndef fvMatrixFunctions_hpp
#define fvMatrixFunctions_hpp


//---------------------------------------------------------------------------
#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "fvMatrices.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  //---------------------------------------------------------------------------
  template< class Type >
  inline fvMatrixHolder< Type > operator + ( const fvMatrixHolder< Type >& mt1, 
                                             const fvMatrixHolder< Type >& mt2 )
  {
    return fvMatrixHolder< Type >( mt1() + mt2(), Deps( mt1.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator - ( const fvMatrixHolder< Type >& mt1, 
                                             const fvMatrixHolder< Type >& mt2 )
  {
    return fvMatrixHolder< Type >( mt1() - mt2(), Deps( mt1.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator + ( const fvMatrixHolder< Type >& mt1, 
                                             const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
  {
    return fvMatrixHolder< Type >( mt1() + field() , Deps( mt1.deps() ) );
  }
  
  template< class Type >
  inline fvMatrixHolder< Type > operator - ( const fvMatrixHolder< Type >& mt1, 
                                             const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
  {
    return fvMatrixHolder< Type >( mt1() - field() , Deps( mt1.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator == ( const fvMatrixHolder< Type >& mt1, 
                                              const fvMatrixHolder< Type >& mt2 )
  {
    return fvMatrixHolder< Type >( mt1() == mt2(), Deps( mt1.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator == ( const fvMatrixHolder< Type >& mt1, 
                                              const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
  {
    return fvMatrixHolder< Type >( mt1() == field() , Deps( mt1.deps() ) );
  }
  
  
  //---------------------------------------------------------------------------
} // Foam


//---------------------------------------------------------------------------
#endif
