//---------------------------------------------------------------------------
#include "TimeHolder_010701.hpp"


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

  SimpleHolder* TimeHolder::clone() const
  {
    return new TimeHolder( *this );
  }

  TimeHolder::~TimeHolder()
  {}

} //Foam


//---------------------------------------------------------------------------
