//---------------------------------------------------------------------------
#include "GeometricFieldArgs.hpp"

#include "fvMeshHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  GeometricFieldArgs::GeometricFieldArgs( const Deps& args ) 
    : universalArgs( args )
  {}

  GeometricFieldArgs::GeometricFieldArgs() 
    : universalArgs()
  {}
 
}


//---------------------------------------------------------------------------

