//---------------------------------------------------------------------------
#include "fvScalarMatrixArgs.H"
#include "fvMeshHolder.H"
#include "volFields.H"


//---------------------------------------------------------------------------
namespace Foam
{
  fvScalarMatrixArgs::fvScalarMatrixArgs( const volScalarFieldHolder& field, 
					  const fvMeshHolder & fvmh ) 
    : fieldArg( new volScalarFieldHolder( field) )
    , fvMeshArg( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& fvScalarMatrixArgs::get_fvMeshArg() const
  {
    return *fvMeshArg;
  }

  const volScalarFieldHolder& fvScalarMatrixArgs::get_fieldArg() const
  {
    return *fieldArg;
  }
}


//---------------------------------------------------------------------------
