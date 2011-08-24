#include "dictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  dictionaryHolder::dictionaryHolder( const boost::shared_ptr< dictionary >& dict )
    : boost::shared_ptr< dictionary >( dict )
    , universalHolder()
  {}

  dictionaryHolder::dictionaryHolder()
    : boost::shared_ptr< dictionary >( new dictionary() )
    , universalHolder()
  {}
}//Foam


//---------------------------------------------------------------------------

