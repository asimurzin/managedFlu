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
    public boost::shared_ptr< IOdictionary >,
    protected dictionaryHolder,
    protected IOobjectHolder
  {
  protected:
    IOdictionaryHolder( const boost::shared_ptr<Foam::IOdictionary>& );
    IOdictionaryHolder();
  private:
//    IOdictionaryHolder( const IOdictionaryHolder& ); // not implemented 
    void operator = ( const IOdictionaryHolder& ); // not implemented 
  public:
    IOdictionaryHolder( const IOobjectHolder& );
    IOdictionaryHolder( const IOobjectHolder&, const dictionaryHolder& );
    using boost::shared_ptr< IOdictionary >::operator->;
    using boost::shared_ptr< IOdictionary >::operator*;
  };
} // Foam


//---------------------------------------------------------------------------
#endif
