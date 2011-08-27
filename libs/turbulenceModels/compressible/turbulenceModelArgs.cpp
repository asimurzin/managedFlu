//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  turbulenceModelArgs::turbulenceModelArgs( 
    const universalHolder* rho, 
    const universalHolder* U, 
    const universalHolder* phi, 
    const universalHolder* thermo )
    : universalArgs( rho, U, phi, thermo )
  {}

  turbulenceModelArgs::turbulenceModelArgs()
    : universalArgs()
  {}

}//compressible

}//Foam



//---------------------------------------------------------------------------
