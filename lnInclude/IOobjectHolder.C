#ifndef IOobjectHolder_C
#define IOobjectHolder_C


//---------------------------------------------------------------------------
#include "IOobjectHolder.H"
#include "objectRegistryHolder.H"
#include "fluIOobject.H"


//---------------------------------------------------------------------------
Foam::IOobjectHolder::IOobjectHolder( const word &name, 
                                      const fileName &instance, 
                                      const objectRegistryHolder & registry, 
                                      IOobject::readOption r, 
                                      IOobject::writeOption w, 
                                      bool registerObject )
  : boost::shared_ptr< IOobject >( new fluIOobject( name, instance, registry, r, w, registerObject ) )
{}

Foam::IOobjectHolder::IOobjectHolder() : boost::shared_ptr< IOobject >()
{}

Foam::IOobjectHolder::IOobjectHolder( const boost::shared_ptr< IOobject >& IOptr ) : boost::shared_ptr< IOobject >( IOptr )
{}


//---------------------------------------------------------------------------
#endif
