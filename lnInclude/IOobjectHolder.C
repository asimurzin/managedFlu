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
    boost::shared_ptr< objectRegistry >( registry ),
    boost::shared_ptr< IOobject >( new IOobject( name, instance, *registry, r, w, registerObject ) )
  {
    cout << "IOobjectHolder = " << this << nl;
  }

  IOobjectHolder::IOobjectHolder() : 
    boost::shared_ptr< objectRegistry >(),
    boost::shared_ptr< IOobject >()
  {
    cout << "IOobjectHolder = " << this << nl;
  }

  IOobjectHolder::IOobjectHolder( const boost::shared_ptr< objectRegistry >& ob ):
    boost::shared_ptr< objectRegistry >( ob ),
    boost::shared_ptr< IOobject >(  ob )
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
