#ifndef geometricFieldFunctionsMM_H
#define geometricFieldFunctionsMM_H


//---------------------------------------------------------------------------
#include "surfaceScalarFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  inline surfaceScalarFieldHolder mag( const surfaceScalarFieldHolder&  field)
  {
    return surfaceScalarFieldHolder( mag( field() ), field.get_fvMeshArg() );
  }

  inline surfaceScalarFieldHolder operator+ ( const surfaceScalarFieldHolder& field1, const surfaceScalarFieldHolder& field2 )
  {
    return surfaceScalarFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
  }


  //-------------------------------------------------------------------------
  inline surfaceVectorFieldHolder operator+ ( const surfaceVectorFieldHolder& field1, const surfaceVectorFieldHolder& field2 )
  {
    return surfaceVectorFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
  }

  inline surfaceScalarFieldHolder operator& ( const surfaceVectorFieldHolder& field1, const surfaceVectorField& field2 )
  {
    return surfaceScalarFieldHolder( field1() & field2, field1.get_fvMeshArg() );
  }

  //-------------------------------------------------------------------------
  inline volVectorFieldHolder operator+ ( const volVectorFieldHolder& field1, const volVectorFieldHolder& field2 )
  {
    return volVectorFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
  }

  volVectorFieldHolder operator- ( const volVectorFieldHolder& field )
  {
    return volVectorFieldHolder( -field(), field.get_fvMeshArg() );
  }

  //-------------------------------------------------------------------------
  inline volScalarFieldHolder operator+ ( const volScalarFieldHolder& field1, const volScalarFieldHolder& field2 )
  {
    return volScalarFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
  }



} // Foam


//---------------------------------------------------------------------------
#endif
