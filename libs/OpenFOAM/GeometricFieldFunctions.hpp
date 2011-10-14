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
  inline surfaceScalarFieldHolder mag( const surfaceScalarFieldHolder&  field )
  {
    return surfaceScalarFieldHolder( mag( field() ), &field );
  }
  
  inline surfaceScalarFieldHolder operator + ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() + field2(), Deps( &field1, &field2 ) );
  }

  inline surfaceScalarFieldHolder operator * ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() * field2(), Deps( &field1, &field2 ) );
  }

  inline surfaceScalarFieldHolder operator - ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() - field2(), Deps( &field1, &field2 ) );
  }

  inline surfaceScalarFieldHolder operator - ( const surfaceScalarFieldHolder& field )
  {
    return surfaceScalarFieldHolder( -field(), &field );
  }


  //-------------------------------------------------------------------------
  inline surfaceVectorFieldHolder operator + ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceVectorFieldHolder( field1() + field2(), Deps( &field1, &field2 ) );
  }

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
  inline volVectorFieldHolder operator + ( const volVectorFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() + field2(), Deps( &field1, &field2 ) );
  }

  inline volVectorFieldHolder operator - ( const volVectorFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() - field2(), Deps( &field1, &field2 ) );
  }

  volVectorFieldHolder operator - ( const volVectorFieldHolder& field )
  {
    return volVectorFieldHolder( -field(), &field );
  }
  
  inline volScalarFieldHolder operator & ( const uniformDimensionedVectorField& field1, 
                                           const volVectorFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1 & field2(), &field2 );
  }


  //-------------------------------------------------------------------------
  inline volScalarFieldHolder mag( const volScalarFieldHolder&  field)
  {
    return volScalarFieldHolder( mag( field() ), &field );
  }

  inline volScalarFieldHolder operator + ( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1() + field2(), Deps( &field1, &field2 ) );
  }

  inline volScalarFieldHolder operator / ( const scalar& value, 
					   const volScalarFieldHolder& field )
  {
    return volScalarFieldHolder( value / field(), Deps( &field ) );
  }
  
  inline volVectorFieldHolder operator * ( const volScalarFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() * field2(), Deps( &field1, &field2 ) );
  }

  inline volScalarFieldHolder operator * ( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1() * field2(), Deps( &field1, &field2 ) );
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

  template< class Type1, class Type2, template<class> class PatchField, class GeoMesh >
  inline GeometricFieldHolder< Type1, PatchField, GeoMesh > operator / ( const GeometricFieldHolder< Type1, PatchField, GeoMesh >& field1, 
                                                                         const GeometricFieldHolder< Type2, PatchField, GeoMesh >& field2 )
  {
    return GeometricFieldHolder< Type1, PatchField, GeoMesh >( field1() / field2(), Deps( &field1, &field2 ) );
  }

  inline volScalarFieldHolder operator - ( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1() - field2(), Deps( &field1, &field2 ) );
  }

  
} // Foam


//---------------------------------------------------------------------------
#endif
