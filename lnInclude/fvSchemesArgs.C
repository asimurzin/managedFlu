#ifndef fvSchemesArgs_C
#define fvSchemesArgs_C


//---------------------------------------------------------------------------
#include "fvSchemesArgs.H"
#include "IOobjectHolder.H"

//---------------------------------------------------------------------------
Foam::fvSchemesArgs::fvSchemesArgs() : IOdictionaryArgs()
{}

Foam::fvSchemesArgs::fvSchemesArgs( const IOobjectHolder& io ) : IOdictionaryArgs( io )
{}


//---------------------------------------------------------------------------
#endif
