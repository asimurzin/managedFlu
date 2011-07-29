#ifndef IOobjectHolder_H
#define IOobjectHolder_H


//---------------------------------------------------------------------------
#include <IOobject.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
  
  class IOobjectHolder : public boost::shared_ptr< IOobject >
  {
  public:
    IOobjectHolder( const word &name, 
                    const fileName &instance, 
                    const objectRegistryHolder & registry, 
                    IOobject::readOption r=IOobject::NO_READ, 
                    IOobject::writeOption w=IOobject::NO_WRITE, 
                    bool registerObject=true );
  protected:  
    IOobjectHolder();
  private:
    // IOobjectHolder( const IOobjectHolder& ); // not implemented 
    void operator = ( const IOobjectHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
