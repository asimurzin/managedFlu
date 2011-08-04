#ifndef IOdictionaryArgs_C
#define IOdictionaryArgs_C


//---------------------------------------------------------------------------
#include "IOdictionaryArgs.H"
#include "dictionaryHolder.H"
#include "IOobjectHolder.H"



//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder&  ioh ) : 
    IOobjectArg( new IOobjectHolder( ioh ) ),
    dictionaryArg()
  {}

  IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder& ioh, const dictionaryHolder& dict ) : 
    IOobjectArg( new IOobjectHolder( ioh ) ),
    dictionaryArg( new dictionaryHolder( dict ) )
  {}

}//Foam


//---------------------------------------------------------------------------
#endif
