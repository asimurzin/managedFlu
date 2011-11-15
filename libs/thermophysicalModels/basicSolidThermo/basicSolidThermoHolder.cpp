//---------------------------------------------------------------------------
#include "basicSolidThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicSolidThermoHolder::basicSolidThermoHolder() 
    : DependentHolder()
    , boost::shared_ptr< basicSolidThermo >()
  {}

  basicSolidThermoHolder::basicSolidThermoHolder( const boost::shared_ptr< basicSolidThermo >& pThermo, const fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< basicSolidThermo >( pThermo )
  {
     boost::shared_ptr< IOdictionary >::operator=( boost::shared_ptr< basicSolidThermo >( *this ) );
  }

  basicSolidThermoHolder basicSolidThermoHolder::New( const fvMeshHolder& mesh )
  {
    autoPtr< basicSolidThermo > pThermo = basicSolidThermo::New( *mesh );
    
    return basicSolidThermoHolder( boost::shared_ptr< basicSolidThermo >( pThermo.ptr() ), mesh );
  }

  void basicSolidThermoHolder::operator=( const boost::shared_ptr< basicSolidThermo >& bt ) 
  {
    boost::shared_ptr< basicSolidThermo >::operator=( bt );
    boost::shared_ptr< IOdictionary >::operator=( boost::shared_ptr< basicSolidThermo >( *this ) );
  }

  SimpleHolder* basicSolidThermoHolder::clone() const
  {
    return new basicSolidThermoHolder( *this );
  }
  
  basicSolidThermoHolder::~basicSolidThermoHolder()
  {}
  
  void basicSolidThermoHolder::operator()( const basicSolidThermoHolder& the_Arg )
  {
    this->operator=( the_Arg );
  }

}


//---------------------------------------------------------------------------
