//---------------------------------------------------------------------------
#include "fvMeshArgs.hpp"

#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshArgs::fvMeshArgs( const universalHolder* ioh ) 
    : universalArgs( ioh )
  {}

fvMeshArgs::fvMeshArgs() 
    : universalArgs()
  {}

}


//---------------------------------------------------------------------------
