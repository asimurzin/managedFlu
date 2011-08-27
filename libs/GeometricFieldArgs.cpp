//---------------------------------------------------------------------------
#include "GeometricFieldArgs.hpp"

#include "fvMeshHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  GeometricFieldArgs::GeometricFieldArgs( const universalHolder* args ) 
    : universalArgs( args )
  {}

  GeometricFieldArgs::GeometricFieldArgs( const std::set< holderPtr >& the_deps ) 
    : universalArgs( the_deps )
  {}

/*
  GeometricFieldArgs::GeometricFieldArgs( const universalHolder* args, const universalHolder* args1 ) 
    : universalArgs( args, args1 )
  {}

  GeometricFieldArgs::GeometricFieldArgs( const universalHolder* args, const universalHolder* args1, const universalHolder* args2 ) 
    : universalArgs( args, args1, args2 )
  {}
*/
  GeometricFieldArgs::GeometricFieldArgs() 
    : universalArgs()
  {}
 
}


//---------------------------------------------------------------------------

