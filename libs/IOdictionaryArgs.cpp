//---------------------------------------------------------------------------
#include "IOdictionaryArgs.hpp"

#include "dictionaryHolder.hpp"
#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder&  ioh ) 
    : universalArgs( new IOobjectHolder( ioh ) )
    , IOobjectArg( new IOobjectHolder( ioh ) )
    , dictionaryArg()
    
  {}

  IOdictionaryArgs::IOdictionaryArgs( const IOobjectHolder& ioh, 
				      const dictionaryHolder& dict ) 
    : universalArgs( new IOobjectHolder( ioh ), new dictionaryHolder( dict ) )
    , IOobjectArg( new IOobjectHolder( ioh ) )
    , dictionaryArg( new dictionaryHolder( dict ) )
  {}

  IOdictionaryArgs::IOdictionaryArgs() 
    : universalArgs()
    , IOobjectArg()
    , dictionaryArg()
  {}

}//Foam


//---------------------------------------------------------------------------
