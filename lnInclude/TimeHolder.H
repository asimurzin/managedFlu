#ifndef TimeHolder_H
#define TimeHolder_H


//---------------------------------------------------------------------------
#include <Time.H>
#include <boost/shared_ptr.hpp>
#include "objectRegistryHolder.H"


namespace Foam
{
  class TimeHolder : public boost::shared_ptr< Time >, public objectRegistryHolder
  {
  public:
    TimeHolder( const word &name, 
                const argList &args, 
                const word &systemName="system", 
                const word &constantName="constant" );
    TimeHolder();
  protected:
    TimeHolder( const boost::shared_ptr< Time >&  t );
  private:
    //TimeHolder(); // not implemented
    // TimeHolder( const TimeHolder& ); // not implemented 
    void operator = ( const TimeHolder& ); // not implemented 
  public:
    using boost::shared_ptr< Time >::operator->;
    using boost::shared_ptr< Time >::operator*;
  };
} // Foam

#endif
