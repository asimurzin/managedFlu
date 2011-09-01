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
    : public IOobjectHolder 
    , public boost::shared_ptr<objectRegistry>
    
  {
  public:
    objectRegistryHolder();

    virtual SimpleHolder* clone() const;
    
    using boost::shared_ptr< objectRegistry >::operator*;
  protected:
    void operator=( const boost::shared_ptr<objectRegistry>& );

  };
} // Foam


//---------------------------------------------------------------------------
#endif
