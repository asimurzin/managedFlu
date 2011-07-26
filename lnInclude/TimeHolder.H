#ifndef TimeHolder_H
#define TimeHolder_H


//---------------------------------------------------------------------------
#include <Time.H>
#include <boost/shared_ptr.hpp>
#include "fluTime.H"
#include "objectRegistryHolder.H"


namespace Foam
{
  class TimeHolder : public boost::shared_ptr< Time >, public objectRegistryHolder
  {
  public:
    TimeHolder( const word &name, 
                const argList &args, 
                const word &systemName="system", 
                const word &constantName="constant" ) 
      : boost::shared_ptr< Time >( new fluTime( name, args, systemName, constantName ) )
      , objectRegistryHolder( boost::shared_ptr< Time >( *this ) )
    {}
  protected:
    TimeHolder( const boost::shared_ptr< Time >&  t ) 
      : boost::shared_ptr< Time >( t )
      , objectRegistryHolder( t ) 
    {} 
  private:
    TimeHolder(); // not implemented
    // TimeHolder( const TimeHolder& ); // not implemented 
    void operator = ( const TimeHolder& ); // not implemented 
  public:
    using boost::shared_ptr< Time >::operator->;
    using boost::shared_ptr< Time >::operator*;
  };
} // Foam

#endif
