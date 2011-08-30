#ifndef linear_hpp
#define linear_hpp


//---------------------------------------------------------------------------
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <linear.H>


//---------------------------------------------------------------------------
namespace Foam
{
  inline surfaceVectorFieldHolder linearInterpolate( const volVectorFieldHolder& field )
  {
    return surfaceVectorFieldHolder( linearInterpolate( field() ) , deps( &field ) );
  }
} // Foam


//---------------------------------------------------------------------------
#endif
