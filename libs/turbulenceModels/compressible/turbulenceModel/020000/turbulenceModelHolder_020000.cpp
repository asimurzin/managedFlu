//---------------------------------------------------------------------------
#include "turbulenceModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{

  turbulenceModelHolder::turbulenceModelHolder()
    : DependentHolder()
    , boost::shared_ptr< turbulenceModel >()
  {}

  turbulenceModelHolder::turbulenceModelHolder( const boost::shared_ptr< turbulenceModel >& tm, 
                                                const volScalarFieldHolder& rho,
                                                const volVectorFieldHolder& U,
                                                const surfaceScalarFieldHolder& phi, 
                                                const basicThermoHolder& thermoPhysicalModel )
    : DependentHolder( Deps( &rho, &U, &phi, &thermoPhysicalModel ) )
    , boost::shared_ptr< turbulenceModel >( tm )
  {}

  turbulenceModelHolder turbulenceModelHolder::New( const volScalarFieldHolder& rho, const volVectorFieldHolder& U,
                                                    const surfaceScalarFieldHolder& phi, const basicThermoHolder& thermoPhysicalModel,
                                                    const word& turbulenceModelName )
  {
    autoPtr< turbulenceModel > result = turbulenceModel::New( rho(), U(), phi(), *thermoPhysicalModel, turbulenceModelName );
    
    return turbulenceModelHolder( boost::shared_ptr< turbulenceModel >( result.ptr() ), rho, U, phi, thermoPhysicalModel );
  }

  SimpleHolder* turbulenceModelHolder::clone() const
  {
    return new turbulenceModelHolder( *this );
  }

  turbulenceModelHolder::~turbulenceModelHolder()
  {}

  void turbulenceModelHolder::operator=( const boost::shared_ptr< turbulenceModel >& tm )
  {
    boost::shared_ptr< turbulenceModel >::operator=( tm );
  }
  
  void turbulenceModelHolder::operator()( const turbulenceModelHolder& the_Arg )
  {
    this->operator=( the_Arg );
  }

  
}//compressible
}//Foam

//---------------------------------------------------------------------------
