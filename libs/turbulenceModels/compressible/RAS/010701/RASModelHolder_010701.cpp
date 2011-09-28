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
    : DependentHolder( Deps( &rho, &U, &phi, &thermo ) )
    , boost::shared_ptr< RASModel >( tm )
  {
    turbulenceModelHolder::operator=( boost::shared_ptr< RASModel >( *this ) );
  }

  RASModelHolder::RASModelHolder()
    : DependentHolder()
    , boost::shared_ptr< RASModel >()
  {}

  RASModelHolder RASModelHolder::New( 
    const volScalarFieldHolder& rho,
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    const basicThermoHolder& thermo )
  {
    autoPtr< RASModel > result = RASModel::New( rho(), U(), phi(), *thermo );
    
    return RASModelHolder( boost::shared_ptr< RASModel >( result.ptr() ), rho, U, phi, thermo );
  }

  SimpleHolder* RASModelHolder::clone() const
  {
    return new RASModelHolder( *this );
  }

  RASModelHolder::~RASModelHolder()
  {}
  
}//compressible
}//Foam

//---------------------------------------------------------------------------
