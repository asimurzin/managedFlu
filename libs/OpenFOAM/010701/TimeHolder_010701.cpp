//---------------------------------------------------------------------------
#include "TimeHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  TimeHolder::TimeHolder( const word &name, 
			  const fileName& rootPath,
			  const fileName& caseName,
			  const word &systemName, 
			  const word &constantName ) 
    : DependentHolder()
    , boost::shared_ptr< Time >( new Time( name, rootPath, caseName, systemName, constantName ) )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< Time >( *this ) );
  }
  
  TimeHolder::TimeHolder( Time* the_time, const Deps& the_deps)
    : DependentHolder( the_deps )
    , boost::shared_ptr< Time >( the_time )
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
