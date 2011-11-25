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
#ifndef fvmLaplacian_010701_hpp
#define fvmLaplacian_010701_hpp


//---------------------------------------------------------------------------
#include <fvmLaplacian.H>
#include "volFields.hpp"
#include "surfaceFields.hpp"
#include "fvMatrices.hpp"

//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    template< class Type, class GType >
    inline fvMatrixHolder< Type > laplacian( const dimensioned< GType >& ds, 
                                             GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
    {
      return fvMatrixHolder< Type >( laplacian( ds, field() ), Deps( &field ) );
    }

    template< class Type, class GType >
    inline fvMatrixHolder< Type > laplacian( const dimensioned< GType >& ds, 
                                             GeometricFieldHolder< Type, fvPatchField, volMesh >& field,
                                             const word& name )
    {
      return fvMatrixHolder< Type >( laplacian( ds, field(), name ), Deps( &field ) );
    }
    
    template< class Type, class GType >
    inline fvMatrixHolder< Type > laplacian( const GeometricFieldHolder< GType, fvPatchField, volMesh >& field1, 
					     GeometricFieldHolder< Type, fvPatchField, volMesh >& field2 )
    {
      return fvMatrixHolder< Type >( laplacian( field1(), field2() ), Deps( &field1, &field2 )  );
    }
   
    template< class Type, class GType >
    inline fvMatrixHolder< Type > laplacian( const GeometricFieldHolder< GType, fvPatchField, volMesh >& field1, 
					     GeometricFieldHolder< Type, fvPatchField, volMesh >& field2
					     const word& name )
    {
      return fvMatrixHolder< Type >( laplacian( field1(), field2(), name ), Deps( &field1, &field2 )  );
    }

    template< class Type, class GType >
    inline fvMatrixHolder< Type > laplacian( const GeometricFieldHolder< GType, vsPatchField, surfaceMesh >& field1, 
					     GeometricFieldHolder< Type, fvPatchField, volMesh >& field2 )
    {
      return fvMatrixHolder< Type >( laplacian( field1(), field2() ), Deps( &field1, &field2 )  );
    }
   
    template< class Type, class GType >
    inline fvMatrixHolder< Type > laplacian( const GeometricFieldHolder< GType, vsPatchField, surfaceMesh >& field1, 
					     GeometricFieldHolder< Type, fvPatchField, volMesh >& field2
					     const word& name )
    {
      return fvMatrixHolder< Type >( laplacian( field1(), field2(), name ), Deps( &field1, &field2 )  );
    }
  } // fvm
} //Foam


//---------------------------------------------------------------------------
#endif

