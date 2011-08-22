//---------------------------------------------------------------------------
#include "basicThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicThermoHolder::basicThermoHolder( const boost::shared_ptr< basicThermo >& bt, const fvMeshHolder& mesh ) 
    : basicThermoArgs( mesh )
    , boost::shared_ptr< basicThermo >( bt )
  {
  }

  basicThermoHolder::~basicThermoHolder()
  {
#ifdef OUR_DEBUG
    cout << "~basicThermoHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
