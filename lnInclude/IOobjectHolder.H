#ifndef IOobjectHolder_H
#define IOobjectHolder_H


//---------------------------------------------------------------------------
#include <IOobject.H>
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
   
  class IOobjectHolder : 
    public boost::shared_ptr< objectRegistry >,
    public boost::shared_ptr< IOobject >
  {
  public:
    IOobjectHolder( const word &name, 
                    const fileName &instance, 
                    const objectRegistryHolder & registry, 
                    IOobject::readOption r=IOobject::NO_READ, 
                    IOobject::writeOption w=IOobject::NO_WRITE, 
                    bool registerObject=true );
    IOobjectHolder( const boost::shared_ptr< objectRegistry >& );
    ~IOobjectHolder();
    using  boost::shared_ptr< IOobject >::operator*;
    using  boost::shared_ptr< IOobject >::operator->;
    
  protected:  
    IOobjectHolder();
  private:
    // IOobjectHolder( const IOobjectHolder& ); // not implemented 
    void operator = ( const IOobjectHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
