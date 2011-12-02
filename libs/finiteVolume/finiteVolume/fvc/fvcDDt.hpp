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
#ifndef fvcDDt_hpp
#define fvcDDt_hpp


//---------------------------------------------------------------------------
#if FOAM_NOT_BRANCH( __FREEFOAM__ )
#include <fvcDDt.H>
#else
#include <fvcDDt_subst.H>
#endif

#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
   template<class Type>
   inline GeometricFieldHolder< Type, fvPatchField, volMesh> DDt( const surfaceScalarFieldHolder& field1,
                                                                  const GeometricFieldHolder< Type, fvPatchField, volMesh >& field2 )
    
   {
     return GeometricFieldHolder< Type, fvPatchField, volMesh >( DDt( field1(), field2() ), Deps( field1.deps(), field2.deps() ) );
   }
   
   template<class Type>
   inline GeometricFieldHolder< typename Foam::flux<Type>::type, fvsPatchField, surfaceMesh > ddtPhiCorr( 
     const volScalarFieldHolder& rA,
     const GeometricFieldHolder<Type, fvPatchField, volMesh>& U,
     const GeometricFieldHolder< typename Foam::flux<Type>::type, fvsPatchField, surfaceMesh >& phi )
    {
      return GeometricFieldHolder< typename Foam::flux<Type>::type, fvsPatchField, surfaceMesh >( ddtPhiCorr( rA(), U(), phi() ), Deps( rA.deps(), U.deps(), phi.deps() ) );
    }      
   
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
