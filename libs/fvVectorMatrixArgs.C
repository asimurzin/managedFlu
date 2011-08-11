//---------------------------------------------------------------------------
#include "fvVectorMatrixArgs.H"
#include "fvMeshHolder.H"
#include "volFields.H"


//---------------------------------------------------------------------------
namespace Foam
{
  fvVectorMatrixArgs::fvVectorMatrixArgs( const volVectorFieldHolder& field, 
					  const fvMeshHolder & fvmh ) 
    : fieldArg( new volVectorFieldHolder( field) )
    , fvMeshArg( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& fvVectorMatrixArgs::get_fvMeshArg() const
  {
    return *fvMeshArg;
  }

  const volVectorFieldHolder& fvVectorMatrixArgs::get_fieldArg() const
  {
    return *fieldArg;
  }
}


//---------------------------------------------------------------------------
