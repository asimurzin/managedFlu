//---------------------------------------------------------------------------
#include "basicThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicThermoHolder::basicThermoHolder( const boost::shared_ptr< basicThermo >& bt, const fvMeshHolder& mesh ) 
    : basicThermoArgs( Foam::deps( &mesh ) )
    , boost::shared_ptr< basicThermo >( bt )
    , universalHolder()
  {}

  basicThermoHolder::basicThermoHolder() 
    : basicThermoArgs()
    , boost::shared_ptr< basicThermo >()
    , universalHolder()
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
