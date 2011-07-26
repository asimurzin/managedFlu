#ifndef objectRegistryHolder_H
#define objectRegistryHolder_H


//---------------------------------------------------------------------------
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>
namespace Foam
{
  class objectRegistryHolder : public boost::shared_ptr< objectRegistry >
  {
  protected:
    objectRegistryHolder( const boost::shared_ptr< objectRegistry >& registry )
      : boost::shared_ptr< objectRegistry >( registry )
    {}
  private:
    objectRegistryHolder(); // not implemented 
    void operator = ( const objectRegistryHolder& registry ); // not implemented 
  };
} // Foam

#endif
