#ifndef TimeHolder_C
#define TimeHolder_C


//---------------------------------------------------------------------------
#include "TimeHolder.H"
#include "fluTime.H"


//---------------------------------------------------------------------------
Foam::TimeHolder::TimeHolder( const word &name, 
                              const argList &args, 
                              const word &systemName, 
                              const word &constantName ) : 
  boost::shared_ptr< Time >( new Time( name, args, systemName, constantName ) )
  , objectRegistryHolder( boost::shared_ptr< Time >( *this ) )
{}


Foam::TimeHolder::TimeHolder()
  : boost::shared_ptr< Time >()
  , objectRegistryHolder() 
{}

//---------------------------------------------------------------------------
#endif
