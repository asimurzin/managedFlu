#ifndef dictionaryHolder_hpp
#define dictionaryHolder_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"

#include <dictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class dictionaryHolder 
    : public boost::shared_ptr< dictionary >
    , virtual public universalHolder
  {
  public:
    virtual universalHolder* clone() const;
    
  protected:
    dictionaryHolder( const boost::shared_ptr< dictionary >& );
    dictionaryHolder();

  };
} // Foam


//---------------------------------------------------------------------------
#endif
