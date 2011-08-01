#ifndef IOdictionaryHolder_C
#define IOdictionaryHolder_C


//---------------------------------------------------------------------------
#include "IOdictionaryHolder.H"
#include "fluIOdictionary.H"



//---------------------------------------------------------------------------
Foam::IOdictionaryHolder::IOdictionaryHolder() : 
  boost::shared_ptr< IOdictionary >(),
  dictionaryHolder(),
  IOobjectHolder()
{}

Foam::IOdictionaryHolder::IOdictionaryHolder( const boost::shared_ptr<Foam::IOdictionary>& obr ) : 
  boost::shared_ptr< IOdictionary >( obr ),
  dictionaryHolder( boost::shared_ptr< IOdictionary >( *this ) ),
  IOobjectHolder( boost::shared_ptr< IOdictionary >( *this ) )
{}


Foam::IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) : 
  boost::shared_ptr< IOdictionary >( new fluIOdictionary( ioh ) ),
  dictionaryHolder(),
  IOobjectHolder( ioh )
{}

Foam::IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, const dictionaryHolder& dict ) : 
  boost::shared_ptr< IOdictionary >( new fluIOdictionary( ioh, dict ) ),
  dictionaryHolder( dict ),
  IOobjectHolder( ioh )
{}


//---------------------------------------------------------------------------
#endif
