#ifndef objectRegistryArgs_C
#define objectRegistryArgs_C


//---------------------------------------------------------------------------
#include "objectRegistryArgs.H"


//---------------------------------------------------------------------------
Foam::objectRegistryArgs::objectRegistryArgs(): objectRegistryHolder(), TimeHolder(), IOobjectArgs()
{}

Foam::objectRegistryArgs::objectRegistryArgs( const objectRegistryHolder& orh,  
                                              const TimeHolder& th )
                    : objectRegistryHolder( orh ),
                      TimeHolder( th ), 
                      IOobjectArgs( orh )
{}


//---------------------------------------------------------------------------
#endif
