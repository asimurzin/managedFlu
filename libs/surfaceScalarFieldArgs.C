#ifndef surfaceScalarFieldArgs_C
#define surfaceScalarFieldArgs_C


//---------------------------------------------------------------------------
#include "surfaceScalarFieldArgs.H"
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  surfaceScalarFieldArgs::surfaceScalarFieldArgs( const fvMeshHolder & fvmh ) : 
    fvMeshArg( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& surfaceScalarFieldArgs::get_fvMeshArg() const
  {
    return *fvMeshArg;
  }
}


//---------------------------------------------------------------------------
#endif
