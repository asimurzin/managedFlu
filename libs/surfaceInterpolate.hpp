#ifndef surfaceInterpolate_hpp
#define surfaceInterpolate_hpp


//---------------------------------------------------------------------------
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <surfaceInterpolate.H>


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    inline surfaceVectorFieldHolder interpolate( const volVectorFieldHolder& field )
    {
      return surfaceVectorFieldHolder( interpolate( field() ), createArgs( field ) );
    }
  }
} // Foam


//---------------------------------------------------------------------------
#endif
