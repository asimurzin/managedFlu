#ifndef volVectorFieldArgs_C
#define volVectorFieldArgs_C


//---------------------------------------------------------------------------
#include "volVectorFieldArgs.H"
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  volVectorFieldArgs::volVectorFieldArgs( const fvMeshHolder & fvmh ) : 
    fvMeshArg( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& volVectorFieldArgs::get_fvMeshArg() const
  {
    return *fvMeshArg;
  }
}


//---------------------------------------------------------------------------
#endif
