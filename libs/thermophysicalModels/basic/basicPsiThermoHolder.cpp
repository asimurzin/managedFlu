//---------------------------------------------------------------------------
#include "basicPsiThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicPsiThermoHolder::basicPsiThermoHolder( const boost::shared_ptr< basicPsiThermo >& pThermo, const fvMeshHolder& mesh ) 
    : basicThermoArgs( mesh )
    , boost::shared_ptr< basicPsiThermo >( pThermo )
    , basicThermoHolder( boost::shared_ptr< basicPsiThermo >( *this ), mesh )
  {
#ifdef OUR_DEBUG
    cout << "basicPsiThermoHolder = " << this << nl;
#endif
  }

  basicPsiThermoHolder::~basicPsiThermoHolder()
  {
#ifdef OUR_DEBUG
    cout << "~basicPsiThermoHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
