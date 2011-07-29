#ifndef surfaceInterpolationArgs_H
#define surfaceInterpolationArgs_H


//---------------------------------------------------------------------------
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class surfaceInterpolationArgs 
       : private fvMeshHolder
  {
  protected:
    surfaceInterpolationArgs( const fvMeshHolder& orh );
    surfaceInterpolationArgs();
  private:
    // surfaceInterpolationArgs(); // not implemented
    surfaceInterpolationArgs( const surfaceInterpolationArgs& ); // not implemented 
    void operator = ( const surfaceInterpolationArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
