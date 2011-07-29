#ifndef dataArgs_C
#define dataArgs_C


//---------------------------------------------------------------------------
#include "dataArgs.H"
#include "IOobjectHolder.H"

//---------------------------------------------------------------------------
Foam::dataArgs::dataArgs() : IOdictionaryArgs()
{}

Foam::dataArgs::dataArgs( const IOobjectHolder& io ) : IOdictionaryArgs( io )
{}


//---------------------------------------------------------------------------
#endif
