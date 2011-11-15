//---------------------------------------------------------------------------
#include "basicRhoThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicRhoThermoHolder::basicRhoThermoHolder( const boost::shared_ptr< basicRhoThermo >& pThermo, const fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< basicRhoThermo >( pThermo )
  {
    basicThermoHolder::operator=( boost::shared_ptr< basicRhoThermo >( *this ) );
  }

  basicRhoThermoHolder::basicRhoThermoHolder() 
    : basicThermoHolder()
    , boost::shared_ptr< basicRhoThermo >()
  {}

  basicRhoThermoHolder::~basicRhoThermoHolder()
  {}

  SimpleHolder* basicRhoThermoHolder::clone() const
  {
    return new basicRhoThermoHolder( *this );
  }

  basicRhoThermoHolder basicRhoThermoHolder::New( const fvMeshHolder& mesh )
  {
    autoPtr< basicRhoThermo > pThermo = basicRhoThermo::New( *mesh );
    
    return basicRhoThermoHolder( boost::shared_ptr< basicRhoThermo >( pThermo.ptr() ), mesh );
  }
  
  void basicRhoThermoHolder::operator()( const basicRhoThermoHolder& the_Arg )
  {
    this->operator=( the_Arg );
  }


}
//---------------------------------------------------------------------------
