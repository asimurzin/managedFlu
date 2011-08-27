//---------------------------------------------------------------------------
#include "RASModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  RASModelArgs::RASModelArgs( 
    const universalHolder* rho, 
    const universalHolder* U, 
    const universalHolder* phi, 
    const universalHolder* thermo )
    : universalArgs( rho, U, phi, thermo )
  {}

  RASModelArgs::RASModelArgs()
    : universalArgs()
  {}

}//compressible

}//Foam



//---------------------------------------------------------------------------
