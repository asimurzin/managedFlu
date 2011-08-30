//---------------------------------------------------------------------------
#include "IOobjectArgs.hpp"

#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOobjectArgs::IOobjectArgs( const Deps& registry ) 
    : universalArgs( registry )
  {}

  IOobjectArgs::IOobjectArgs() 
    : universalArgs()
  {}
  
}


//---------------------------------------------------------------------------
