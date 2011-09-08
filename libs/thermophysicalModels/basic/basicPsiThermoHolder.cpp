//---------------------------------------------------------------------------
#include "basicPsiThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicPsiThermoHolder::basicPsiThermoHolder( const boost::shared_ptr< basicPsiThermo >& pThermo, const fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< basicPsiThermo >( pThermo )
  {
    basicThermoHolder::operator=( boost::shared_ptr< basicPsiThermo >( *this ) );
  }

  basicPsiThermoHolder::basicPsiThermoHolder() 
    : basicThermoHolder()
    , boost::shared_ptr< basicPsiThermo >()
  {}

  basicPsiThermoHolder::~basicPsiThermoHolder()
  {}

  SimpleHolder* basicPsiThermoHolder::clone() const
  {
    return new basicPsiThermoHolder( *this );
  }

  basicPsiThermoHolder basicPsiThermoHolder::New( const fvMeshHolder& mesh )
  {
    autoPtr< basicPsiThermo > pThermo = basicPsiThermo::New( *mesh );
    
    return basicPsiThermoHolder( boost::shared_ptr< basicPsiThermo >( pThermo.ptr() ), mesh );
  }

}
//---------------------------------------------------------------------------
