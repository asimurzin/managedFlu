//---------------------------------------------------------------------------
#include "basicPsiThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicPsiThermoHolder::basicPsiThermoHolder( const boost::shared_ptr< basicPsiThermo >& pThermo, const fvMeshHolder& mesh ) 
    : DependentHolder( Foam::deps( &mesh ) )
    , boost::shared_ptr< basicPsiThermo >( pThermo )
    , basicThermoHolder( boost::shared_ptr< basicPsiThermo >( *this ), mesh )
  {
#ifdef OUR_DEBUG
    cout << "basicPsiThermoHolder = " << this << nl;
#endif
  }

  basicPsiThermoHolder::basicPsiThermoHolder() 
    : DependentHolder()
    , boost::shared_ptr< basicPsiThermo >()
    , basicThermoHolder()
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
