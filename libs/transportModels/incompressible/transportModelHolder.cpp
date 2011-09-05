//---------------------------------------------------------------------------
#include "transportModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  
  transportModelHolder::transportModelHolder() 
    : IOdictionaryHolder()
    , boost::shared_ptr< transportModel >()
  {}

  void transportModelHolder::operator=( const boost::shared_ptr< transportModel >& bt ) 
  {
    boost::shared_ptr< transportModel >::operator=( bt );
    IOdictionaryHolder::operator=( bt );
  }

  SimpleHolder* transportModelHolder::clone() const
  {
    return new transportModelHolder( *this );
  }
  
  transportModelHolder::~transportModelHolder()
  {}
}


//---------------------------------------------------------------------------
