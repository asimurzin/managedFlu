//---------------------------------------------------------------------------
#include "turbulenceModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  turbulenceModelHolder::turbulenceModelHolder( 
    const boost::shared_ptr< turbulenceModel >& tm, 
    const volScalarFieldHolder& rho, 
    const volVectorFieldHolder& U,  
    const surfaceScalarFieldHolder& phi, 
    const basicThermoHolder& thermo )
    : DependentHolder( Foam::deps( &rho, Foam::deps( &U, Foam::deps( &phi, &thermo ) ) ) )
    , boost::shared_ptr< turbulenceModel >( tm )
  {}

  turbulenceModelHolder::turbulenceModelHolder()
    : DependentHolder()
    , boost::shared_ptr< turbulenceModel >()
  {
#ifdef OUR_DEBUG
    cout << "~turbulenceModelHolder = " << this << nl;
#endif
  }

  universalHolder* turbulenceModelHolder::clone() const
  {
    return new turbulenceModelHolder( *this );
  }

  turbulenceModelHolder::~turbulenceModelHolder()
  {
#ifdef OUR_DEBUG
    cout << "~turbulenceModelHolder = " << this << nl;
#endif
  }
}//compressible
}//Foam

//---------------------------------------------------------------------------
