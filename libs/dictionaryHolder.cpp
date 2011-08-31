#include "dictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  dictionaryHolder::dictionaryHolder( const boost::shared_ptr< dictionary >& dict )
    : SimpleHolder()
    , boost::shared_ptr< dictionary >( dict )
  {}

  dictionaryHolder::dictionaryHolder()
    : SimpleHolder()
    , boost::shared_ptr< dictionary >( new dictionary() )
  {}
  
  SimpleHolder* dictionaryHolder::clone() const
  {
    return new dictionaryHolder( *this );
  }
  
  
}//Foam


//---------------------------------------------------------------------------

