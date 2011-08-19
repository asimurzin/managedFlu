#ifndef GeometricFieldFunctions_hpp
#define GeometricFieldFunctions_hpp


//---------------------------------------------------------------------------
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshHolder get_valid_mesh( const fvMeshHolder& mesh1, const fvMeshHolder& mesh2 )
  {
    if ( mesh1.get() != 0 )
      return mesh1;

    else if ( mesh2.get() != 0 )
      return mesh2;
    
    return mesh1;
  }
  
  fvMeshHolder get_valid_mesh( const fvMeshHolder& mesh1, const fvMeshHolder& mesh2,  const fvMeshHolder& mesh3 )
  {
    if ( mesh1.get() != 0 )
      return mesh1;

    else if ( mesh2.get() != 0 )
      return mesh2;

    else if ( mesh3.get() != 0 )
      return mesh3;
    
    return mesh1;
  }
  
  
  //-------------------------------------------------------------------------
  inline surfaceScalarFieldHolder mag( const surfaceScalarFieldHolder&  field )
  {
    return surfaceScalarFieldHolder( mag( field() ), field.mesh() );
  }
  
  inline surfaceScalarFieldHolder operator + ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() + field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }

  inline surfaceScalarFieldHolder operator - ( const surfaceScalarFieldHolder& field1, 
					       const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() - field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }


  //-------------------------------------------------------------------------
  inline surfaceVectorFieldHolder operator + ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceVectorFieldHolder( field1() + field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }

  inline surfaceScalarFieldHolder operator & ( const surfaceVectorFieldHolder& field1, 
					       const surfaceVectorFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() & field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }


  //-------------------------------------------------------------------------
  inline volVectorFieldHolder operator + ( const volVectorFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() + field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }

  inline volVectorFieldHolder operator - ( const volVectorFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() - field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }

  volVectorFieldHolder operator - ( const volVectorFieldHolder& field )
  {
    return volVectorFieldHolder( -field(), field.mesh() );
  }
  

  //-------------------------------------------------------------------------
  inline volScalarFieldHolder mag( const volScalarFieldHolder&  field)
  {
    return volScalarFieldHolder( mag( field() ), field.mesh() );
  }
  inline volScalarFieldHolder operator + ( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1() + field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }

  inline volScalarFieldHolder operator / ( const scalar& value, 
					   const volScalarFieldHolder& field )
  {
    return volScalarFieldHolder( value / field(), field.mesh() );
  }
  
  inline volVectorFieldHolder operator * ( const volScalarFieldHolder& field1, 
					   const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() * field2(), get_valid_mesh( field1.mesh(), field2.mesh() ) );
  }
} // Foam


//---------------------------------------------------------------------------
#endif
