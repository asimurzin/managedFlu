#ifndef TimeHolder_C
#define TimeHolder_C


//---------------------------------------------------------------------------
#include "TimeHolder.H"
#include "fluTime.H"


//---------------------------------------------------------------------------
namespace Foam
{

  TimeHolder::TimeHolder( const word &name, 
                              const argList &args, 
                              const word &systemName, 
                              const word &constantName ) : 
    boost::shared_ptr< Time >( new Time( name, args, systemName, constantName ) )
    , objectRegistryHolder( boost::shared_ptr< Time >( *this ) )
  {
    cout << "TimeHolder = " << this << nl;
  }


  TimeHolder::TimeHolder()
    : boost::shared_ptr< Time >()
    , objectRegistryHolder() 
  {
    cout << "TimeHolder = " << this << nl;
  }

  TimeHolder::~TimeHolder()
  {
    cout << "~TimeHolder = " << this << nl;
  }


} //Foam


//---------------------------------------------------------------------------
#endif
