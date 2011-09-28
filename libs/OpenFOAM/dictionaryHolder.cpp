#include "dictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  void dictionaryHolder::operator=( const boost::shared_ptr< dictionary >& dict )
  {
    boost::shared_ptr< dictionary >::operator=( dict );
  }

  dictionaryHolder::dictionaryHolder()
    : SimpleHolder()
    , boost::shared_ptr< dictionary >()
  {}
  
  SimpleHolder* dictionaryHolder::clone() const
  {
    return new dictionaryHolder( *this );
  }
  
  
}//Foam


//---------------------------------------------------------------------------

