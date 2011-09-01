//---------------------------------------------------------------------------
#include "basicThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicThermoHolder::basicThermoHolder() 
    : DependentHolder()
    , boost::shared_ptr< basicThermo >()
  {}

  void basicThermoHolder::operator=( const boost::shared_ptr< basicThermo >& bt ) 
  {
    boost::shared_ptr< basicThermo >::operator=( bt );
  }

  SimpleHolder* basicThermoHolder::clone() const
  {
    return new basicThermoHolder( *this );
  }
  
  basicThermoHolder::~basicThermoHolder()
  {}
}


//---------------------------------------------------------------------------
