//---------------------------------------------------------------------------
#include "fvMeshArgs.hpp"
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshArgs::fvMeshArgs( const IOobjectHolder & ioh ) 
    : IOobjectArg( new IOobjectHolder( ioh ) )
  {}
}


//---------------------------------------------------------------------------
