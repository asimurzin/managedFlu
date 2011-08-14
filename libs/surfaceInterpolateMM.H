#ifndef surfaceInterpolateMM_H
#define surfaceInterpolateMM_H


//---------------------------------------------------------------------------
#include <surfaceInterpolate.H>

#include "volFields.hpp"
#include "surfaceFieldsMM.H"


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
