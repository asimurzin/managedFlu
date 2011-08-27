//---------------------------------------------------------------------------
#include "IOdictionaryArgs.hpp"

#include "dictionaryHolder.hpp"
#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryArgs::IOdictionaryArgs( const universalHolder*  ioh ) 
    : universalArgs( ioh )
  {}

  IOdictionaryArgs::IOdictionaryArgs( const universalHolder* ioh, 
				      const universalHolder* dict ) 
    : universalArgs( ioh, dict )
  {}

  IOdictionaryArgs::IOdictionaryArgs() 
    : universalArgs()
  {}

}//Foam


//---------------------------------------------------------------------------
