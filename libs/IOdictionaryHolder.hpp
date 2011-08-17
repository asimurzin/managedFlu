#ifndef IOdictionaryHolder_hpp
#define IOdictionaryHolder_hpp


//---------------------------------------------------------------------------
#include "dictionaryHolder.hpp"
#include "IOobjectHolder.H"
#include "IOdictionaryArgs.hpp"

#include <IOdictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOdictionaryHolder 
    : protected IOdictionaryArgs
    , public boost::shared_ptr< IOdictionary >
    , protected dictionaryHolder
    , protected IOobjectHolder
  {
  public:
    IOdictionaryHolder( const IOobjectHolder& );
    IOdictionaryHolder( const IOobjectHolder&, const dictionaryHolder& );
    IOdictionaryHolder();
    
    ~IOdictionaryHolder();

    using boost::shared_ptr< IOdictionary >::operator->;
    using boost::shared_ptr< IOdictionary >::operator*;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
