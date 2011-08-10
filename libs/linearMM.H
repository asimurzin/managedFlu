#ifndef linearMM_H
#define linearMM_H


//---------------------------------------------------------------------------
#include <linear.H>

#include "volFieldsMM.H"
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
