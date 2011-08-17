//---------------------------------------------------------------------------
#include "fvMeshArgs.hpp"

#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshArgs::fvMeshArgs( const IOobjectHolder & ioh ) 
    : IOobjectArg( new IOobjectHolder( ioh ) )
  {}
}


//---------------------------------------------------------------------------
