//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
//  Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
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

#include <uniformDimensionedFields.H>


//---------------------------------------------------------------------------
namespace Foam
{
  
  //-------------------------------------------------------------------------
  inline surfaceScalarFieldHolder operator & ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() & field2(), Deps( &field1, &field2 ) );
  }

  inline surfaceScalarFieldHolder operator & ( const uniformDimensionedVectorField& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1 & field2(), Deps( &field2 ) );
  }


  //-------------------------------------------------------------------------
  inline volScalarFieldHolder operator & ( const uniformDimensionedVectorField& field1, 
                                           const volVectorFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1 & field2(), &field2 );
  }


  //-------------------------------------------------------------------------
  inline volScalarFieldHolder operator / ( const scalar& value, 
					   const volScalarFieldHolder& field )
  {
    return volScalarFieldHolder( value / field(), Deps( &field ) );
  }
  
  
  //-------------------------------------------------------------------------
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator * ( const GeometricFieldHolder< scalar, PatchField, GeoMesh >& field1, 
                                                                        const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() * field2(), Deps( &field1, &field2 ) );
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
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() + field2(), Deps( &field1, &field2 ) );
  }

 template<class Type, template<class> class PatchField, class GeoMesh>
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator * ( const dimensionedScalar& dmS, 
                                                                        const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( dmS * field2(), Deps( &field2 ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator + ( const dimensionedScalar& dmS, 
                                                                        const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( dmS + field2(), Deps( &field2 ) );
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
    return GeometricFieldHolder< Type1, PatchField, GeoMesh >( field1() / field2(), Deps( &field1, &field2 ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > operator - ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field1, 
					                                const GeometricFieldHolder< Type, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( field1() - field2(), Deps( &field1, &field2 ) );
  }

  template<class Type, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type, PatchField, GeoMesh > mag( const GeometricFieldHolder< Type, PatchField, GeoMesh >&  field )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( mag( field() ), &field );
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh >
  inline  GeometricFieldHolder< Type, PatchField, GeoMesh > operator - ( const  GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    return GeometricFieldHolder< Type, PatchField, GeoMesh >( -field(), &field );
  }

} // Foam


//---------------------------------------------------------------------------
#endif
