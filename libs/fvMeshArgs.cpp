//---------------------------------------------------------------------------
#include "fvMeshArgs.hpp"

#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshArgs::fvMeshArgs( const Deps& arg ) 
    : universalArgs( arg )
  {}

fvMeshArgs::fvMeshArgs() 
    : universalArgs()
  {}

}


//---------------------------------------------------------------------------
