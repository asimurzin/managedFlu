#ifndef transportModelHolder_hpp
#define transportModelHolder_hpp


//---------------------------------------------------------------------------
#include "IOdictionaryHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <transportModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class transportModelHolder 
    : public IOdictionaryHolder
    , public boost::shared_ptr< transportModel >
  {
  public:

    transportModelHolder();
    
    ~transportModelHolder();
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< transportModel >::operator*;
    using  boost::shared_ptr< transportModel >::operator->;
  protected:
    void operator=( const boost::shared_ptr< transportModel >& );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
