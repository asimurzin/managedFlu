#ifndef IOdictionaryArgs_C
#define IOdictionaryArgs_C


//---------------------------------------------------------------------------
#include "IOdictionaryArgs.H"


//---------------------------------------------------------------------------
Foam::IOdictionaryArgs::IOdictionaryArgs() : IOobjectHolder(),
                                             dictionaryArgs()
{}

Foam::IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder& io ):IOobjectHolder( io ),
                                                                     dictionaryArgs()
{
}


//---------------------------------------------------------------------------
#endif
