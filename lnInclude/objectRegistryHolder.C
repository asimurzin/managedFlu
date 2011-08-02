#ifndef objectRegistryHolder_C
#define objectRegistryHolder_C


//---------------------------------------------------------------------------
#include "objectRegistryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  objectRegistryHolder::objectRegistryHolder() :
    IOobjectHolder()
  {}

  objectRegistryHolder::objectRegistryHolder( const boost::shared_ptr<Foam::objectRegistry>& obr ) :
     IOobjectHolder( obr )
  {}

}


//---------------------------------------------------------------------------
#endif
