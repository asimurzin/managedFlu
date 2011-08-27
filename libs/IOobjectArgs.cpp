//---------------------------------------------------------------------------
#include "IOobjectArgs.hpp"

#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOobjectArgs::IOobjectArgs( const universalHolder* registry ) 
    : universalArgs( registry )
  {}

  IOobjectArgs::IOobjectArgs() 
    : universalArgs()
  {}
  
}


//---------------------------------------------------------------------------
