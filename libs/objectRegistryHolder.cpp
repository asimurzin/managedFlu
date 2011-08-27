//---------------------------------------------------------------------------
#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  objectRegistryHolder::objectRegistryHolder( const boost::shared_ptr< objectRegistry >& obr ) 
     : boost::shared_ptr< objectRegistry >( obr )
     , IOobjectHolder()
  {}

  universalHolder* objectRegistryHolder::clone() const
  {
    return new objectRegistryHolder( *this );
  }

  objectRegistryHolder::objectRegistryHolder() 
    : boost::shared_ptr< objectRegistry >(  )
    , IOobjectHolder()
  {}

} //Foam


//---------------------------------------------------------------------------
