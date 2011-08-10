#ifndef IOobjectArgs_C
#define IOobjectArgs_C


//---------------------------------------------------------------------------
#include "IOobjectArgs.H"
#include "objectRegistryHolder.H"


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
#endif
