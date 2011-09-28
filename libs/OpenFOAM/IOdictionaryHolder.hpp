#ifndef IOdictionaryHolder_hpp
#define IOdictionaryHolder_hpp


//---------------------------------------------------------------------------
#include "dictionaryHolder.hpp"
#include "IOobjectHolder.hpp"
#include "Args.hpp"
#include "Deps.hpp"
#include "DependentHolder.hpp"

#include <IOdictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOdictionaryHolder 
    : public dictionaryHolder
    , public IOobjectHolder
    , public boost::shared_ptr< IOdictionary >
  {
  public:
    IOdictionaryHolder( const IOobjectHolder& );
    IOdictionaryHolder( const IOobjectHolder&, const dictionaryHolder& );
    IOdictionaryHolder();
    
    ~IOdictionaryHolder();
    
    virtual SimpleHolder* clone() const;

    using boost::shared_ptr< IOdictionary >::operator->;
    using boost::shared_ptr< IOdictionary >::operator*;
  protected:
    void operator=( const boost::shared_ptr< IOdictionary >& );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
