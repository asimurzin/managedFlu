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
    : turbulenceModelArgs( rho, U, phi, thermo )
    , boost::shared_ptr< RASModel >( tm )
  {
  }

  RASModelHolder RASModelHolder::New( 
    const volScalarFieldHolder& rho ,  
    const volVectorFieldHolder& U, 
    const surfaceScalarFieldHolder& phi, 
    const basicThermoHolder& thermo )
  {
    autoPtr< RASModel > result = RASModel::New( rho(), U(), phi(), *thermo );
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
