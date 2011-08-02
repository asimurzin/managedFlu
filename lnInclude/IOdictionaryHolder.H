#ifndef IOdictionaryHolder_H
#define IOdictionaryHolder_H


//---------------------------------------------------------------------------
#include <IOdictionary.H>
#include <boost/shared_ptr.hpp>
#include "dictionaryHolder.H"
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class IOdictionaryHolder : 
    protected IOobjectHolder,
    public boost::shared_ptr< IOdictionary >,
    protected dictionaryHolder
  {
  public:
    IOdictionaryHolder( const IOobjectHolder& );
    IOdictionaryHolder( const IOobjectHolder&, const dictionaryHolder& );
    ~IOdictionaryHolder();
    using boost::shared_ptr< IOdictionary >::operator->;
    using boost::shared_ptr< IOdictionary >::operator*;
  protected:
    IOdictionaryHolder();
  private:
//    IOdictionaryHolder( const IOdictionaryHolder& ); // not implemented 
    void operator = ( const IOdictionaryHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
