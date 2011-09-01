//---------------------------------------------------------------------------
#include "IOobjectHolder.hpp"

#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IOobjectHolder::IOobjectHolder( const word &name, 
                                  const fileName &instance, 
                                  const objectRegistryHolder & registry, 
                                  IOobject::readOption r, 
                                  IOobject::writeOption w, 
                                  bool registerObject ) 
    : DependentHolder( Foam::deps( &registry )  )
    , boost::shared_ptr< IOobject >( new IOobject( name, instance, *registry, r, w, registerObject ) )
  {}
  
  void IOobjectHolder::operator=( const boost::shared_ptr< IOobject >& ioPtr )
  {
   boost::shared_ptr< IOobject >::operator=( ioPtr );
  }
  
  IOobjectHolder::IOobjectHolder() 
    : DependentHolder()
    , boost::shared_ptr< IOobject >()
  {}

  SimpleHolder* IOobjectHolder::clone() const
  {
    return new IOobjectHolder( *this );
  }

  IOobjectHolder::~IOobjectHolder()
  {}
}


//---------------------------------------------------------------------------
