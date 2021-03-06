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
#ifndef GeometricFieldFunctions_hpp
#define GeometricFieldFunctions_hpp


//---------------------------------------------------------------------------
#include "surfaceFields.hpp"
#include "volFields.hpp"

#include <uniformDimensionedFieldHolders.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  //-------------------------------------------------------------------------
  template <class Type1, class Type2, template<class> class PatchField, class GeoMesh>
  inline GeometricFieldHolder<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>
    operator & ( const GeometricFieldHolder< Type1, PatchField, GeoMesh >& field1, 
                 const GeometricFieldHolder< Type2, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder<typename innerProduct<Type1, Type2>::type, PatchField, GeoMesh>( field1() & field2(), Deps( field1.deps(), field2.deps() ) );
  }

  
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< typename innerProduct< vector, Type >::type, PatchField, GeoMesh >
    operator & ( const uniformDimensionedVectorFieldHolder& field1, 
                 const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< typename innerProduct< vector, Type >::type, PatchField, GeoMesh >( *field1 & field2(), Deps( field1.deps(), field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< typename innerProduct< vector, Type >::type, PatchField, GeoMesh >
    operator & ( const vector& theVector, 
                 const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    return GeometricFieldHolder< typename innerProduct< vector, Type >::type, PatchField, GeoMesh >( theVector & field(), Deps( field.deps() ) );
  }

  template< template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< scalar, PatchField, GeoMesh > 
    operator / ( const scalar& value, 
                 const GeometricFieldHolder< scalar, PatchField, GeoMesh >& field )
  {
    return GeometricFieldHolder< scalar, PatchField, GeoMesh >( value / field(), Deps( field.deps() ) );
  }
  
  template< template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< scalar, PatchField, GeoMesh > 
    operator / ( const dimensionedScalar& dmS, 
                 const GeometricFieldHolder< scalar, PatchField, GeoMesh >& field )
  {
    return GeometricFieldHolder< scalar, PatchField, GeoMesh >( dmS / field(), Deps( field.deps() ) );
  }
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator * ( const GeometricFieldHolder< scalar, PatchField, GeoMesh >& field1, 
                                                                        const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() * field2(), Deps( field1.deps(), field2.deps() ) );
  }
  /*
    
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator * ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field1, 
	                                                                const GeometricFieldHolder< scalar, PatchField, GeoMesh >& field2 )
  { 
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() * field2(), Deps( &field1, &field2 ) );
  }

  */
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator + ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field1, 
					                                const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() + field2(), Deps( field1.deps(), field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator * ( const dimensionedScalar& dmS, 
                                                                        const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( dmS * field2(), Deps( field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator * ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2, 
                                                                        const dimensionedScalar& dmS )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field2() * dmS, Deps( field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator + ( const dimensioned< Type >& dmT, 
                                                                        const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( dmT + field2(), Deps( field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator / ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2,
                                                                        const dimensionedScalar& dmS )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field2() / dmS, Deps( &field2 ) );
  }

  template< class Type1, class Type2, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type1, PatchField, GeoMesh > operator / ( const GeometricFieldHolder< Type1, PatchField, GeoMesh >& field1, 
                                                                         const GeometricFieldHolder< Type2, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type1, PatchField, GeoMesh >( field1() / field2(), Deps( field1.deps(), field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator - ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field1, 
					                                const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() - field2(), Deps( field1.deps(), field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator - ( const scalar& theValue, 
					                                const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( theValue - field2(), Deps( field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator - ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2,
                                                                        const scalar& theValue )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field2() - theValue, Deps( field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< scalar, PatchField, GeoMesh > mag( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field )
  {
    return GeometricFieldHolder< scalar, PatchField, GeoMesh >( mag( field() ), Deps( field.deps() ) );
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline  GeometricFieldHolder< Type, PatchField, GeoMesh > operator - ( const  GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( -field(), Deps( field.deps() ) );
  }
  
  template< template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< scalar, PatchField, GeoMesh > pos( const GeometricFieldHolder< scalar, PatchField, GeoMesh >&  field )
  {
    return GeometricFieldHolder< scalar, PatchField, GeoMesh >( pos( field() ), Deps( field.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > max( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field1,
                                                                const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( max( field1(), field2() ), Deps( field1.deps(), field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > min( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field1,
                                                                const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( min( field1(), field2() ), Deps( field1.deps(), field2.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > max( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field1,
                                                                const dimensioned< Type >& dmT )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( max( field1(), dmT ), Deps( field1.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > min( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field1,
                                                                const dimensioned< Type >& dmT )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( min( field1(), dmT ), Deps( field1.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > max( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field1,
                                                                const Type& theValue )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( max( field1(), theValue ), Deps( field1.deps() ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > min( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field1,
                                                                const Type& theValue )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( min( field1(), theValue ), Deps( field1.deps() ) );
  }

} // Foam


//---------------------------------------------------------------------------
#endif
