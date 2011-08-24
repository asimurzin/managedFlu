//---------------------------------------------------------------------------
#include "IOobjectArgs.hpp"

#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOobjectArgs::IOobjectArgs( const objectRegistryHolder& registry ) 
    : universalArgs( new objectRegistryHolder( registry ) )
    , objectRegistryArg( new objectRegistryHolder( registry ) )
  {}

  IOobjectArgs::IOobjectArgs() 
    : universalArgs()
    , objectRegistryArg( )
  {}
  
  const objectRegistryHolder& IOobjectArgs::get_objectRegistryArg() const
  {
    return *objectRegistryArg;
  }
}


//---------------------------------------------------------------------------
