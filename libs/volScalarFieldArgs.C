#ifndef volScalarFieldArgs_C
#define volScalarFieldArgs_C


//---------------------------------------------------------------------------
#include "volScalarFieldArgs.H"
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  volScalarFieldArgs::volScalarFieldArgs( const fvMeshHolder & fvmh ) : 
    fvMeshArg( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& volScalarFieldArgs::get_fvMeshArg() const
  {
    return *fvMeshArg;
  }
}


//---------------------------------------------------------------------------
#endif
