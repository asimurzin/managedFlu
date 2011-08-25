//---------------------------------------------------------------------------
#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  objectRegistryHolder::objectRegistryHolder( const boost::shared_ptr< objectRegistry >& obr ) 
     : boost::shared_ptr< objectRegistry >( obr )
     , IOobjectHolder()
  {}

  objectRegistryHolder::objectRegistryHolder( const IOobjectHolder& io ) 
    : boost::shared_ptr< objectRegistry >( io.get_objectRegistryArg() )
    , IOobjectHolder( io )
  {}

  universalHolder* objectRegistryHolder::clone()
  {
    return new objectRegistryHolder( *this );
  }

  objectRegistryHolder::objectRegistryHolder() 
    : boost::shared_ptr< objectRegistry >(  )
    , IOobjectHolder()
  {}

} //Foam


//---------------------------------------------------------------------------
