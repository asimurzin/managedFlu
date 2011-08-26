#ifndef GeometricFieldFunctions_hpp
#define GeometricFieldFunctions_hpp


//---------------------------------------------------------------------------
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  
  //-------------------------------------------------------------------------
  inline surfaceScalarFieldHolder mag( const surfaceScalarFieldHolder&  field )
  {
    return surfaceScalarFieldHolder( mag( field() ), createArgs( field ) );
  }
  
  inline surfaceScalarFieldHolder operator + ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() + field2(), createArgs( field1, field2 ) );
  }

  inline surfaceScalarFieldHolder operator + ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarField& field2 )
  {
    return surfaceScalarFieldHolder( field1() + field2, createArgs( field1 ) );
  }


  inline surfaceScalarFieldHolder operator - ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() - field2(), createArgs( field1, field2 ) );
  }


  //-------------------------------------------------------------------------
  inline surfaceVectorFieldHolder operator + ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceVectorFieldHolder( field1() + field2(), createArgs( field1, field2 ) );
  }

  inline surfaceScalarFieldHolder operator & ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() & field2(), createArgs( field1, field2 ) );
  }

  inline surfaceScalarFieldHolder operator & ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorField& field2 )
  {
    return surfaceScalarFieldHolder( field1() & field2, createArgs( field1 ) );
  }



  //-------------------------------------------------------------------------
  inline volVectorFieldHolder operator + ( const volVectorFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() + field2(), createArgs( field1, field2 ) );
  }

  inline volVectorFieldHolder operator - ( const volVectorFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() - field2(), createArgs( field1, field2 ) );
  }

  volVectorFieldHolder operator - ( const volVectorFieldHolder& field )
  {
    return volVectorFieldHolder( -field(), createArgs( field ) );
  }
  

  //-------------------------------------------------------------------------
  inline volScalarFieldHolder mag( const volScalarFieldHolder&  field)
  {
    return volScalarFieldHolder( mag( field() ), createArgs( field ) );
  }
  inline volScalarFieldHolder operator + ( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1() + field2(), createArgs( field1, field2 ) );
  }

  inline volScalarFieldHolder operator / ( const scalar& value, 
					   const volScalarFieldHolder& field )
  {
    return volScalarFieldHolder( value / field(), createArgs( field ) );
  }
  
  inline volVectorFieldHolder operator * ( const volScalarFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() * field2(), createArgs( field1, field2 ) );
  }
  
  inline volVectorFieldHolder operator * ( const volScalarFieldHolder& field1, 
					   const volVectorField& field2 )
  {
    return volVectorFieldHolder( field1() * field2, createArgs( field1 ) );
  }

  inline volVectorFieldHolder operator * ( const volScalarFieldHolder& field1, 
					   const tmp< volVectorField >& field2 )
  {
    return volVectorFieldHolder( field1() * field2, createArgs( field1 ) );
  }


} // Foam


//---------------------------------------------------------------------------
#endif
