#ifndef objectRegistryHolder_hpp
#define objectRegistryHolder_hpp


//---------------------------------------------------------------------------
#include "IOobjectHolder.hpp"

#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder 
    : public boost::shared_ptr<objectRegistry>
    , public IOobjectHolder 
  {
  public:
    objectRegistryHolder();
    using boost::shared_ptr< objectRegistry >::operator*;
    
    virtual universalHolder* clone() const;

  protected:
    objectRegistryHolder( const boost::shared_ptr<objectRegistry>& );
    objectRegistryHolder( const IOobjectHolder& );

  };
} // Foam


//---------------------------------------------------------------------------
#endif
