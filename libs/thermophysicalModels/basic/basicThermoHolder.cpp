//---------------------------------------------------------------------------
#include "basicThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicThermoHolder::basicThermoHolder( const boost::shared_ptr< basicThermo >& bt, const fvMeshHolder& mesh ) 
    : DependentHolder( Foam::deps( &mesh ) )
    , boost::shared_ptr< basicThermo >( bt )
  {}

  basicThermoHolder::basicThermoHolder() 
    : DependentHolder()
    , boost::shared_ptr< basicThermo >()
  {}

  universalHolder* basicThermoHolder::clone() const
  {
    return new basicThermoHolder( *this );
  }
  
  basicThermoHolder::~basicThermoHolder()
  {
#ifdef OUR_DEBUG
    cout << "~basicThermoHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
