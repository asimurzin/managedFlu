//---------------------------------------------------------------------------
#include "IOdictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) 
    : DependentHolder( Foam::deps( &ioh ) )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh ) )
    , dictionaryHolder( boost::shared_ptr< IOdictionary >( *this ) )
    , IOobjectHolder( boost::shared_ptr< IOdictionary >( *this ) )
  {
#ifdef OUR_DEBUG
    cout << "IOdictionaryHolder = " << this << nl;
#endif
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, 
					  const dictionaryHolder& dict ) 
    : DependentHolder( Foam::deps( &ioh, &dict ) )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh, *dict ) )
    , dictionaryHolder( boost::shared_ptr< IOdictionary >( *this ) )
    , IOobjectHolder( boost::shared_ptr< IOdictionary >( *this ) )
  {
#ifdef OUR_DEBUG
    cout << "IOdictionaryHolder = " << this << nl;
#endif
  }

  IOdictionaryHolder::IOdictionaryHolder() 
    : DependentHolder()
    , boost::shared_ptr< IOdictionary >()
    , dictionaryHolder()
    , IOobjectHolder()
  {
#ifdef OUR_DEBUG
    cout << "IOdictionaryHolder = " << this << nl;
#endif
  }

  SimpleHolder* IOdictionaryHolder::clone() const
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
