//---------------------------------------------------------------------------
#include "RASModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  RASModelArgs::RASModelArgs( 
    const volScalarFieldHolder& rho, 
    const volVectorFieldHolder& U, 
    const surfaceScalarFieldHolder& phi, 
    const basicThermoHolder& thermo )
    : turbulenceModelArgs( rho, U, phi, thermo )
  {}

}//compressible

}//Foam



//---------------------------------------------------------------------------
