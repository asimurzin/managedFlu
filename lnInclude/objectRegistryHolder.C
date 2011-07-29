#ifndef objectRegistryHolder_C
#define objectRegistryHolder_C


//---------------------------------------------------------------------------
#include "objectRegistryHolder.H"


//---------------------------------------------------------------------------
Foam::objectRegistryHolder::objectRegistryHolder():boost::shared_ptr< objectRegistry >(),
                                                   IOobjectHolder()
                                                   
{}

Foam::objectRegistryHolder::objectRegistryHolder( const boost::shared_ptr<Foam::objectRegistry>& obr ): boost::shared_ptr< objectRegistry >( obr ),
                                                                                                        IOobjectHolder( boost::shared_ptr< objectRegistry >( *this ) )
                                                                                                        
{}


//---------------------------------------------------------------------------
#endif
