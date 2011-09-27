#ifndef TimeHolder_010700_hpp
#define TimeHolder_010700_hpp


//---------------------------------------------------------------------------
#include "objectRegistryHolder.hpp"

#include <Time.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class TimeHolder 
    : public objectRegistryHolder
    , public boost::shared_ptr< Time >
  {
  public:
    TimeHolder( const word& name,
                const fileName& rootPath,
                const fileName& caseName,
                const word& systemName = "system",
                const word& constantName = "constant" );
    TimeHolder( Time*, const Deps& );
    //TimeHolder( const Time*, const Deps& ); will be implemented after change shared_ptr with smart_ptr

    virtual SimpleHolder* clone() const;
    
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
