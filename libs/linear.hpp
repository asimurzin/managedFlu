#ifndef linear_hpp
#define linear_hpp


//---------------------------------------------------------------------------
#include <linear.H>

#include "volFields.hpp"
#include "surfaceFieldsMM.H"


//---------------------------------------------------------------------------
namespace Foam
{
  inline surfaceVectorFieldHolder linearInterpolate( const volVectorFieldHolder& field )
  {
    return surfaceVectorFieldHolder( linearInterpolate( field() ) , field.mesh() );
  }
} // Foam


//---------------------------------------------------------------------------
#endif
