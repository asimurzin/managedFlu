#ifndef objectRegistryArgs_C
#define objectRegistryArgs_C


//---------------------------------------------------------------------------
#include "objectRegistryArgs.H"


//---------------------------------------------------------------------------
Foam::objectRegistryArgs::objectRegistryArgs(): TimeHolder(), IOobjectArgs()
{}

Foam::objectRegistryArgs::objectRegistryArgs( const objectRegistryHolder& orh,  
                                              const TimeHolder& th )
                    : TimeHolder( th ), 
                      IOobjectArgs( orh )
{}


//---------------------------------------------------------------------------
#endif
