#ifndef surfaceVectorFieldArgs_C
#define surfaceVectorFieldArgs_C


//---------------------------------------------------------------------------
#include "surfaceVectorFieldArgs.H"
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  surfaceVectorFieldArgs::surfaceVectorFieldArgs( const fvMeshHolder & fvmh ) : 
    fvMeshArg( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& surfaceVectorFieldArgs::get_fvMeshArg() const
  {
    return *fvMeshArg;
  }
}


//---------------------------------------------------------------------------
#endif
