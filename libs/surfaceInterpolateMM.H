#ifndef surfaceInterpolateMM_H
#define surfaceInterpolateMM_H


//---------------------------------------------------------------------------
#include <surfaceInterpolate.H>

#include "volVectorFieldHolder.H"
#include "surfaceVectorFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    inline surfaceVectorFieldHolder interpolate( const volVectorFieldHolder& field )
    {
      return surfaceVectorFieldHolder( interpolate( field() ) , field.get_fvMeshArg() );
    }
  }

} // Foam


//---------------------------------------------------------------------------
#endif
