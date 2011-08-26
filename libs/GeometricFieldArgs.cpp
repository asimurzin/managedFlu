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

  GeometricFieldArgs::GeometricFieldArgs( const universalHolder* args ) 
    : universalArgs( args )
    , mesh_()
  {}

  GeometricFieldArgs::GeometricFieldArgs( const universalHolder* args, const universalHolder* args1 ) 
    : universalArgs( args, args1 )
    , mesh_()
  {}

  GeometricFieldArgs::GeometricFieldArgs( const universalHolder* args, const universalHolder* args1, const universalHolder* args2 ) 
    : universalArgs( args, args1, args2 )
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

