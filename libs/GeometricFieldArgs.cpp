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
 
  fvMeshHolder GeometricFieldArgs::mesh() const
  {
    if ( mesh_ )
      return *mesh_;
    else
      return fvMeshHolder();
  }
}


//---------------------------------------------------------------------------

