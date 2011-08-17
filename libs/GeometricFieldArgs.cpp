//---------------------------------------------------------------------------
#include "GeometricFieldArgs.hpp"
#include "fvMeshHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  GeometricFieldArgs::GeometricFieldArgs( const fvMeshHolder & fvmh ) 
    : mesh_( new fvMeshHolder( fvmh ) )
  {}

  GeometricFieldArgs::GeometricFieldArgs() 
    : mesh_()
  {}
 
  const fvMeshHolder& GeometricFieldArgs::mesh() const
  {
    return *mesh_;
  }
}


//---------------------------------------------------------------------------

