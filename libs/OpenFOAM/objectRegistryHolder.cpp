//---------------------------------------------------------------------------
#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  void objectRegistryHolder::operator=( const boost::shared_ptr< objectRegistry >& obr ) 
  {
    boost::shared_ptr< objectRegistry >::operator=( boost::shared_ptr< objectRegistry >( obr ) );
    IOobjectHolder::operator=( boost::shared_ptr< objectRegistry >( *this ) );
  }

  SimpleHolder* objectRegistryHolder::clone() const
  {
    return new objectRegistryHolder( *this );
  }

  objectRegistryHolder::objectRegistryHolder() 
    : IOobjectHolder()
    , boost::shared_ptr< objectRegistry >()
  {}

} //Foam


//---------------------------------------------------------------------------
