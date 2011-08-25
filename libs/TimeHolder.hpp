#ifndef TimeHolder_hpp
#define TimeHolder_hpp


//---------------------------------------------------------------------------
#include "objectRegistryHolder.hpp"

#include <Time.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class TimeHolder 
    : public boost::shared_ptr< Time >
    , public objectRegistryHolder
  {
  public:
    TimeHolder( const word &name, 
                const argList &args, 
                const word &systemName="system", 
                const word &constantName="constant" );

    virtual universalHolder* clone() const;
    
    ~TimeHolder();

    using boost::shared_ptr< Time >::operator->;
    using boost::shared_ptr< Time >::operator*;

  private:
    TimeHolder(); // not implemented
    // TimeHolder( const TimeHolder& ); // not implemented 
    void operator = ( const TimeHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
