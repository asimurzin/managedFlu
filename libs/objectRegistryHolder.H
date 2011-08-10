#ifndef objectRegistryHolder_H
#define objectRegistryHolder_H


//---------------------------------------------------------------------------
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder 
    : public boost::shared_ptr<objectRegistry>
    , public IOobjectHolder 
  {
  public:
    using boost::shared_ptr< objectRegistry >::operator*;

  protected:
    objectRegistryHolder( const boost::shared_ptr<objectRegistry>& );
    objectRegistryHolder( const IOobjectHolder& );

  private:
    // objectRegistryHolder( const objectRegistryHolder& ); // not implemented 
    void operator = ( const objectRegistryHolder& ); // not implemented 
    objectRegistryHolder(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
