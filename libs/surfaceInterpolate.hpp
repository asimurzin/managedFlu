#ifndef surfaceInterpolate_hpp
#define surfaceInterpolate_hpp


//---------------------------------------------------------------------------
#include <surfaceInterpolate.H>

#include "volFields.hpp"
#include "surfaceFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    inline surfaceVectorFieldHolder interpolate( const volVectorFieldHolder& field )
    {
      return surfaceVectorFieldHolder( interpolate( field() ), field.mesh() );
    }
  }
} // Foam


//---------------------------------------------------------------------------
#endif
