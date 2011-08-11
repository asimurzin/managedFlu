#ifndef fvMeshArgs_C
#define fvMeshArgs_C


//---------------------------------------------------------------------------
#include "fvMeshArgs.H"
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshArgs::fvMeshArgs( const IOobjectHolder & ioh ) 
    : IOobjectArg( new IOobjectHolder( ioh ) )
  {}
}


//---------------------------------------------------------------------------
#endif
