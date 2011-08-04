#ifndef IOobjectHolder_C
#define IOobjectHolder_C


//---------------------------------------------------------------------------
#include "IOobjectHolder.H"
#include "objectRegistryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  IOobjectHolder::IOobjectHolder( const word &name, 
                                  const fileName &instance, 
                                  const objectRegistryHolder & registry, 
                                  IOobject::readOption r, 
                                  IOobject::writeOption w, 
                                  bool registerObject ) : 
    IOobjectArgs( registry ),
    boost::shared_ptr< IOobject >( new IOobject( name, instance, *registry, r, w, registerObject ) )
  {
    cout << "IOobjectHolder = " << this << nl;
  }
 
  IOobjectHolder::IOobjectHolder() : 
    IOobjectArgs()
    , boost::shared_ptr< IOobject >()
  {
    cout << "IOobjectHolder = " << this << nl;
  }

  IOobjectHolder::~IOobjectHolder()
  {
    cout << "~IOobjectHolder = " << this << nl;
  }
}


//---------------------------------------------------------------------------
#endif
