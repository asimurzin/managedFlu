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
    : virtual public DependentHolder
    , public boost::shared_ptr< IOdictionary >
    , public dictionaryHolder
    , public IOobjectHolder
  {
  public:
    IOdictionaryHolder( const IOobjectHolder& );
    IOdictionaryHolder( const IOobjectHolder&, const dictionaryHolder& );
    IOdictionaryHolder();
    
    ~IOdictionaryHolder();
    
    virtual SimpleHolder* clone() const;

    using boost::shared_ptr< IOdictionary >::operator->;
    using boost::shared_ptr< IOdictionary >::operator*;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
