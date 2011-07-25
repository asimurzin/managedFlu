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
    objectRegistryHolder( objectRegistry* registry ):boost::shared_ptr< objectRegistry >( registry ){}
  private:
    objectRegistryHolder( const objectRegistryHolder& ); // not implemented 
    objectRegistryHolder(); // not implemented 
  };
} // Foam

#endif
