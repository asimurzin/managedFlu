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
    : DependentHolder( Foam::deps( &registry ) )
    , boost::shared_ptr< IOobject >( new IOobject( name, instance, *registry, r, w, registerObject ) )
  {
#ifdef OUR_DEBUG
    cout << "IOobjectHolder = " << this << nl;
#endif
  }
 
  IOobjectHolder::IOobjectHolder() 
    : DependentHolder()
    , boost::shared_ptr< IOobject >()
  {
#ifdef OUR_DEBUG
    cout << "IOobjectHolder = " << this << nl;
#endif
  }

  universalHolder* IOobjectHolder::clone() const
  {
    return new IOobjectHolder( *this );
  }

  IOobjectHolder::~IOobjectHolder()
  {
#ifdef OUR_DEBUG
    cout << "~IOobjectHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
