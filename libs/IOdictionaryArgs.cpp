//---------------------------------------------------------------------------
#include "IOdictionaryArgs.hpp"

#include "dictionaryHolder.hpp"
#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder&  ioh ) 
    : IOobjectArg( new IOobjectHolder( ioh ) )
    , dictionaryArg()
  {}

  IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder& ioh, 
				      const dictionaryHolder& dict ) 
    : IOobjectArg( new IOobjectHolder( ioh ) )
    , dictionaryArg( new dictionaryHolder( dict ) )
  {}

  IOdictionaryArgs::IOdictionaryArgs() 
    : IOobjectArg()
    , dictionaryArg()
  {}

}//Foam


//---------------------------------------------------------------------------
