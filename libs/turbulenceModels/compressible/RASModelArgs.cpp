//---------------------------------------------------------------------------
#include "RASModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  RASModelArgs::RASModelArgs( const Deps& arg )
    : universalArgs( arg )
  {}

  RASModelArgs::RASModelArgs()
    : universalArgs()
  {}

}//compressible

}//Foam



//---------------------------------------------------------------------------
