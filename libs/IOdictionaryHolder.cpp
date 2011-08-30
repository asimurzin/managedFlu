//---------------------------------------------------------------------------
#include "IOdictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) 
    : universalArgs( Foam::deps( &ioh ) )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh ) )
    , dictionaryHolder()
    , IOobjectHolder( ioh )
  {
#ifdef OUR_DEBUG
    cout << "IOdictionaryHolder = " << this << nl;
#endif
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, 
					  const dictionaryHolder& dict ) 
    : universalArgs( Foam::deps( &ioh, &dict ) )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh, *dict ) )
    , dictionaryHolder( dict )
    , IOobjectHolder( ioh )
  {
#ifdef OUR_DEBUG
    cout << "IOdictionaryHolder = " << this << nl;
#endif
  }

  IOdictionaryHolder::IOdictionaryHolder() 
    : universalArgs()
    , boost::shared_ptr< IOdictionary >()
    , dictionaryHolder()
    , IOobjectHolder()
  {
#ifdef OUR_DEBUG
    cout << "IOdictionaryHolder = " << this << nl;
#endif
  }

  universalHolder* IOdictionaryHolder::clone() const
  {
    return new IOdictionaryHolder( *this );
  }

  IOdictionaryHolder::~IOdictionaryHolder()
  {
#ifdef OUR_DEBUG
    cout << "~IOdictionaryHolder = " << this << nl;
#endif
  }
}//Foam


//---------------------------------------------------------------------------
