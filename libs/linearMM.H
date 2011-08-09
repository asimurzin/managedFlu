#ifndef linearMM_H
#define linearMM_H


//---------------------------------------------------------------------------
#include <linear.H>

#include "volVectorFieldHolder.H"
#include "surfaceVectorFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  inline surfaceVectorFieldHolder linearInterpolate( const volVectorFieldHolder& field )
  {
    return surfaceVectorFieldHolder( linearInterpolate( field() ) , field.get_fvMeshArg() );
  }

} // Foam


//---------------------------------------------------------------------------
#endif
