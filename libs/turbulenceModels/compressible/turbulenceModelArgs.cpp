//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace compressible
{
  turbulenceModelArgs::turbulenceModelArgs( const Deps& arg )
    : universalArgs( arg )
  {}

  turbulenceModelArgs::turbulenceModelArgs()
    : universalArgs()
  {}

}//compressible

}//Foam



//---------------------------------------------------------------------------
