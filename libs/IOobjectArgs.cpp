//---------------------------------------------------------------------------
#include "IOobjectArgs.hpp"
#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOobjectArgs::IOobjectArgs( const objectRegistryHolder& registry ) 
    : objectRegistryArg( new objectRegistryHolder( registry ) )
  {}

  IOobjectArgs::IOobjectArgs() 
    : objectRegistryArg( )
  {}
  
  const objectRegistryHolder& IOobjectArgs::get_objectRegistryArg() const
  {
    return *objectRegistryArg;
  }
}


//---------------------------------------------------------------------------
