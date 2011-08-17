#ifndef IOobjectHolder_hpp
#define IOobjectHolder_hpp


//---------------------------------------------------------------------------
#include "IOobjectArgs.hpp"

#include <IOobject.H>
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
   
  class IOobjectHolder 
    : public IOobjectArgs
    , public boost::shared_ptr< IOobject >
  {
  public:
    IOobjectHolder( const word &name, 
                    const fileName &instance, 
                    const objectRegistryHolder & registry, 
                    IOobject::readOption r = IOobject::NO_READ, 
                    IOobject::writeOption w = IOobject::NO_WRITE, 
                    bool registerObject=true );
    ~IOobjectHolder();

    using  boost::shared_ptr< IOobject >::operator*;
    using  boost::shared_ptr< IOobject >::operator->;

  protected:
    IOobjectHolder( const boost::shared_ptr< objectRegistry >& ); 
    IOobjectHolder();

  };
} // Foam


//---------------------------------------------------------------------------
#endif