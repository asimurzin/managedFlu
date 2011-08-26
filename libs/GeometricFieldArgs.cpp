//---------------------------------------------------------------------------
#include "GeometricFieldArgs.hpp"

#include "fvMeshHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  GeometricFieldArgs::GeometricFieldArgs( const fvMeshHolder & fvmh ) 
    : universalArgs( new fvMeshHolder( fvmh ) )
    , mesh_( new fvMeshHolder( fvmh ) )
  {}

  GeometricFieldArgs::GeometricFieldArgs( const universalArgs& args ) 
    : universalArgs( args )
    , mesh_()
  {}

  GeometricFieldArgs::GeometricFieldArgs() 
    : universalArgs()
    , mesh_()
  {}
 
  const boost::shared_ptr< fvMeshHolder >& GeometricFieldArgs::mesh() const
  {
      return mesh_;
  }
}


//---------------------------------------------------------------------------

