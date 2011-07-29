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
      public boost::shared_ptr< objectRegistry >
      , protected IOobjectHolder 
      
  {
  protected:
    objectRegistryHolder( const boost::shared_ptr<Foam::objectRegistry>& );
    objectRegistryHolder();
  private:
//    objectRegistryHolder( const objectRegistryHolder& ); // not implemented 
    void operator = ( const objectRegistryHolder& ); // not implemented 
  public:
    using boost::shared_ptr< objectRegistry >::operator*;
  };
} // Foam


//---------------------------------------------------------------------------
#endif
