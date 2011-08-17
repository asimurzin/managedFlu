//---------------------------------------------------------------------------
#include "TimeHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  TimeHolder::TimeHolder( const word &name, 
			  const argList &args, 
			  const word &systemName, 
			  const word &constantName ) 
    : boost::shared_ptr< Time >( new Time( name, args, systemName, constantName ) )
    , objectRegistryHolder( boost::shared_ptr< Time >( *this ) )
  {
#ifdef OUR_DEBUG
    cout << "TimeHolder = " << this << nl;
#endif
  }

  TimeHolder::~TimeHolder()
  {
#ifdef OUR_DEBUG
    cout << "~TimeHolder = " << this << nl;
#endif
  }
} //Foam


//---------------------------------------------------------------------------
