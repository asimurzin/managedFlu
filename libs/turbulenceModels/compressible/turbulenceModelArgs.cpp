//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  turbulenceModelArgs::turbulenceModelArgs( 
    const volScalarFieldHolder& rho, 
    const volVectorFieldHolder& U, 
    const surfaceScalarField& phi, 
    const basicThermoHolder& thermo )
    : rho_( new volScalarFieldHolder( rho ) )
    , U_( new volVectorFieldHolder( U ) )
    , phi_( new surfaceScalarFieldHolder( phi ) )
    , thermophysicalModel_( new basicThermoHolder( thermo ) )
  {}

  const volScalarFieldHolder& turbulenceModelArgs::rho() const
  {
    return *rho_;
  }
  
  const volVectorFieldHolder& turbulenceModelArgs::U() const
  {
    return *U_;
  }

  const surfaceScalarFieldHolder& turbulenceModelArgs::phi() const
  {
    return *phi_;
  }

  const basicThermoHolder& turbulenceModelArgs::thermo() const
  {
    return *thermophysicalModel_;
  }

}//compressible

}//Foam



//---------------------------------------------------------------------------
