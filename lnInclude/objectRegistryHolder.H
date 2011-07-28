#ifndef objectRegistryHolder_H
#define objectRegistryHolder_H


//---------------------------------------------------------------------------
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder : 
      protected IOobjectHolder, 
      public boost::shared_ptr< objectRegistry >
  {
  protected:
    objectRegistryHolder( const boost::shared_ptr<Foam::objectRegistry>& );
  private:
//    objectRegistryHolder( const objectRegistryHolder& ); // not implemented 
    void operator = ( const objectRegistryHolder& ); // not implemented 
  public:
    objectRegistryHolder();
    using boost::shared_ptr< objectRegistry >::operator*;
  };
} // Foam


//---------------------------------------------------------------------------
#endif
