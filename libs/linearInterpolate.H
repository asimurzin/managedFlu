#ifndef linearInterpolate_H
#define linearInterpolate_H


//---------------------------------------------------------------------------
#include <linear.H>

#include "volVectorFieldHolder.H"
#include "surfaceVectorFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  surfaceVectorFieldHolder linearInterpolate( const volVectorFieldHolder& );

} // Foam


//---------------------------------------------------------------------------
#endif
