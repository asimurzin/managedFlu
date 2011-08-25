//---------------------------------------------------------------------------
#include "basicThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicThermoHolder::basicThermoHolder( const boost::shared_ptr< basicThermo >& bt, const fvMeshHolder& mesh ) 
    : basicThermoArgs( mesh )
    , boost::shared_ptr< basicThermo >( bt )
    , universalHolder()
  {
  }

  universalHolder* basicThermoHolder::clone()
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
