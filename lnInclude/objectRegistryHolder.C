#ifndef objectRegistryHolder_C
#define objectRegistryHolder_C


//---------------------------------------------------------------------------
#include "objectRegistryHolder.H"


//---------------------------------------------------------------------------
Foam::objectRegistryHolder::objectRegistryHolder():IOobjectHolder(),
                                                   boost::shared_ptr< objectRegistry >()
{}

Foam::objectRegistryHolder::objectRegistryHolder( const boost::shared_ptr<Foam::objectRegistry>& obr ): IOobjectHolder(),
                                                                                                        boost::shared_ptr< objectRegistry >( obr )
{}


//---------------------------------------------------------------------------
#endif
