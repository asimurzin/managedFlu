#ifndef IOdictionaryHolder_H
#define IOdictionaryHolder_H


//---------------------------------------------------------------------------
#include <IOdictionary.H>
#include <boost/shared_ptr.hpp>
#include "dictionaryHolder.H"
#include "IOobjectHolder.H"
#include "IOdictionaryArgs.H"

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

  private:
    // IOdictionaryHolder( const IOdictionaryHolder& ); // not implemented 
    //void operator = ( const IOdictionaryHolder& ); // not implemented 
    //IOdictionaryHolder(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
