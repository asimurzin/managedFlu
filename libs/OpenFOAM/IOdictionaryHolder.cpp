//---------------------------------------------------------------------------
#include "IOdictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) 
    : DependentHolder( &ioh )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh ) )
  {
    dictionaryHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
    IOobjectHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, 
					  const dictionaryHolder& dict ) 
    : DependentHolder( Deps( &ioh, &dict ) )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh, *dict ) )
  {
    dictionaryHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
    IOobjectHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
  }

  IOdictionaryHolder::IOdictionaryHolder() 
    : DependentHolder()
    , boost::shared_ptr< IOdictionary >()
  {}

  SimpleHolder* IOdictionaryHolder::clone() const
  {
    return new IOdictionaryHolder( *this );
  }
  
  void IOdictionaryHolder::operator=( const boost::shared_ptr< IOdictionary >&  iodic)
  {
    boost::shared_ptr< IOdictionary >::operator=( iodic );
    dictionaryHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
    IOobjectHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
  }
  
  IOdictionaryHolder::~IOdictionaryHolder()
  {}

}//Foam


//---------------------------------------------------------------------------
