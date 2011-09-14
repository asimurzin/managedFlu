//---------------------------------------------------------------------------
#include "TimeHolder_020000.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  TimeHolder::TimeHolder( const word &name, 
			  const argList &args, 
			  const word &systemName, 
			  const word &constantName ) 
    : DependentHolder()
    , boost::shared_ptr< Time >( new Time( name, args, systemName, constantName ) )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< Time >( *this ) );
  }

  SimpleHolder* TimeHolder::clone() const
  {
    return new TimeHolder( *this );
  }

  TimeHolder::~TimeHolder()
  {}

} //Foam


//---------------------------------------------------------------------------
