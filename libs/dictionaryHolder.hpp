#ifndef dictionaryHolder_hpp
#define dictionaryHolder_hpp


//---------------------------------------------------------------------------
#include "Args.hpp"
#include "SimpleHolder.hpp"

#include <dictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class dictionaryHolder 
    : public boost::shared_ptr< dictionary >
    , virtual public SimpleHolder
  {
  public:
    virtual SimpleHolder* clone() const;
    
  protected:
    dictionaryHolder( const boost::shared_ptr< dictionary >& );
    dictionaryHolder();

  };
} // Foam


//---------------------------------------------------------------------------
#endif
