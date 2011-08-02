#ifndef IOdictionaryHolder_C
#define IOdictionaryHolder_C


//---------------------------------------------------------------------------
#include "IOdictionaryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryHolder::IOdictionaryHolder() : 
    IOobjectHolder(),
    boost::shared_ptr< IOdictionary >(),
    dictionaryHolder()
  {
    cout << "IOdictionaryHolder = " << this << nl;
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) : 
    IOobjectHolder( ioh ),
    boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh ) ),
    dictionaryHolder()
  {
    cout << "IOdictionaryHolder = " << this << nl;
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, const dictionaryHolder& dict ) : 
    IOobjectHolder( ioh ),
    boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh, *dict ) ),
    dictionaryHolder( dict )
  {
    cout << "IOdictionaryHolder = " << this << nl;
  }

  IOdictionaryHolder::~IOdictionaryHolder()
  {
    cout << "~IOdictionaryHolder = " << this << nl;
  }

}//Foam


//---------------------------------------------------------------------------
#endif
