//---------------------------------------------------------------------------
#include "GeometricFieldArgs.H"
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  GeometricFieldArgs::GeometricFieldArgs( const fvMeshHolder & fvmh ) : 
    mesh_( new fvMeshHolder( fvmh ) )
  {}

  const fvMeshHolder& GeometricFieldArgs::mesh() const
  {
    return *mesh_;
  }
}


//---------------------------------------------------------------------------

