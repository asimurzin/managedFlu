#ifndef IOobjectHolder_H
#define IOobjectHolder_H


//---------------------------------------------------------------------------
#include <IOobject.H>
#include <boost/shared_ptr.hpp>
#include "fluIOobject.H"
#include "objectRegistryHolder.H"


namespace Foam
{
  class IOobjectHolder : public boost::shared_ptr< IOobject >
  {
  public:
    IOobjectHolder( const word &name, 
                    const fileName &instance, 
                    const objectRegistryHolder & registry, 
                    IOobject::readOption r=IOobject::NO_READ, 
                    IOobject::writeOption w=IOobject::NO_WRITE, 
                    bool registerObject=true ) : boost::shared_ptr< IOobject >( new fluIOobject( name, instance, registry, r, w, registerObject ) )
    {}
  protected:
    IOobjectHolder( const IOobjectHolder&  t ) : boost::shared_ptr< IOobject >( t )
    {} 
  private:
    IOobjectHolder(); // not implemented
  public:
   using boost::shared_ptr< IOobject >::operator*;
  };
} // Foam

#endif
