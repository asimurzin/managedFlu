#ifndef IOdictionaryHolder_C
#define IOdictionaryHolder_C


//---------------------------------------------------------------------------
#include "IOdictionaryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) : 
    IOdictionaryArgs( ioh ),
    boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh ) ),
    dictionaryHolder(),
    IOobjectHolder( ioh )
  {
    cout << "IOdictionaryHolder = " << this << nl;
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, const dictionaryHolder& dict ) : 
    IOdictionaryArgs( ioh, dict ),
    boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh, *dict ) ),
    dictionaryHolder( dict ),
    IOobjectHolder( ioh )
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
