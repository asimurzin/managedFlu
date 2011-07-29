#ifndef fvSolutionArgs_C
#define fvSolutionArgs_C


//---------------------------------------------------------------------------
#include "fvSolutionArgs.H"
#include "IOobjectHolder.H"

//---------------------------------------------------------------------------
Foam::fvSolutionArgs::fvSolutionArgs() : IOdictionaryArgs()
{}

Foam::fvSolutionArgs::fvSolutionArgs( const IOobjectHolder& io ) : IOdictionaryArgs( io )
{}


//---------------------------------------------------------------------------
#endif
