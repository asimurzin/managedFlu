//---------------------------------------------------------------------------
#include "RASModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  RASModelHolder::RASModelHolder( 
    const boost::shared_ptr< RASModel >& tm, 
    const volScalarFieldHolder& rho, 
    const volVectorFieldHolder& U,  
    const surfaceScalarFieldHolder& phi, 
    const basicThermoHolder& thermo )
    : RASModelArgs( rho, U, phi, thermo )
    , boost::shared_ptr< RASModel >( tm )
    , turbulenceModelHolder( boost::shared_ptr< RASModel >( *this ), rho, U, phi, thermo )
  {}

  RASModelHolder RASModelHolder::New( 
    const volScalarFieldHolder& rho,
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    const basicThermoHolder& thermo,
    const word& turbulenceModelName )
  {
    autoPtr< RASModel > result = RASModel::New( rho(), U(), phi(), *thermo, turbulenceModelName );
    
    return RASModelHolder( boost::shared_ptr< RASModel >( result.ptr() ), rho, U, phi, thermo );
  }


  RASModelHolder::~RASModelHolder()
  {
#ifdef OUR_DEBUG
    cout << "~RASModelHolder = " << this << nl;
#endif
  }
}//compressible
}//Foam

//---------------------------------------------------------------------------
