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
#ifndef fvm_hpp
#define fvm_hpp


//---------------------------------------------------------------------------
#include "common.hpp"

#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "fvMatrices.hpp"

#include "fvmLaplacian.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    //-----------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )    
    inline fvVectorMatrixHolder ddt( const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), &field );
    }

    inline fvScalarMatrixHolder ddt( const volScalarFieldHolder& field )
    {
      return fvScalarMatrixHolder( ddt( field() ), &field );
    }

    inline fvVectorMatrixHolder ddt( const volScalarFieldHolder& field1,
                                     const volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( ddt( field1(), field2() ),  Deps( &field1, &field2 ) );
    }

    inline fvScalarMatrixHolder ddt( const volScalarFieldHolder& field1,
                                     const volScalarFieldHolder& field2 )
    {
      return fvScalarMatrixHolder( ddt( field1(), field2() ),  Deps( &field1, &field2 ) );
    }


    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, 
				     const volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( div( field1(), field2() ), Deps( &field1, &field2 ) );
    }
    
#endif

#if FOAM_VERSION( <, 020000 )
    inline fvVectorMatrixHolder ddt( volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), &field );
    }

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, 
				     volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( div( field1(), field2() ), Deps( &field1, &field2 ) );
    }
    

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder laplacian( const dimensionedScalar& ds, 
                                           volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( laplacian( ds, field() ), &field );
    }

    inline fvScalarMatrixHolder laplacian( const volScalarFieldHolder& field1, 
					   volScalarFieldHolder& field2 )
    {
      return fvScalarMatrixHolder( laplacian( field1(), field2() ), Deps( &field1, &field2 )  );
    }
#endif
  } // fvm
} // Foam


//---------------------------------------------------------------------------
#endif
