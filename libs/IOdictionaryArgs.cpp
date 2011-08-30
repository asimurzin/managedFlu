//---------------------------------------------------------------------------
#include "IOdictionaryArgs.hpp"

#include "dictionaryHolder.hpp"
#include "IOobjectHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryArgs::IOdictionaryArgs( const Deps& args ) 
    : universalArgs( args )
  {}

  IOdictionaryArgs::IOdictionaryArgs() 
    : universalArgs()
  {}

}//Foam


//---------------------------------------------------------------------------
