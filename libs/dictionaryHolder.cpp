#include "dictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  dictionaryHolder::dictionaryHolder( const boost::shared_ptr< dictionary >& dict )
    : universalHolder()
    , boost::shared_ptr< dictionary >( dict )
  {}

  dictionaryHolder::dictionaryHolder()
    : universalHolder()
    , boost::shared_ptr< dictionary >( new dictionary() )
  {}
  
  universalHolder* dictionaryHolder::clone() const
  {
    return new dictionaryHolder( *this );
  }
  
  
}//Foam


//---------------------------------------------------------------------------

