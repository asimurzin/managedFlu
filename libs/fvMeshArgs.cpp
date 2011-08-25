//---------------------------------------------------------------------------
#include "fvMeshArgs.hpp"

#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshArgs::fvMeshArgs( const IOobjectHolder & ioh ) 
    : universalArgs( new IOobjectHolder( ioh ) )
    , IOobjectArg( new IOobjectHolder( ioh ) )
  {}

fvMeshArgs::fvMeshArgs() 
    : universalArgs()
    , IOobjectArg()
  {}

}


//---------------------------------------------------------------------------
