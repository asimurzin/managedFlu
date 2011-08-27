//---------------------------------------------------------------------------
#include "radiationModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  radiationModelArgs::radiationModelArgs( const universalHolder* arg ) 
    : universalArgs( arg )
  {}

  radiationModelArgs::radiationModelArgs() 
    : universalArgs()
  {}
}


//---------------------------------------------------------------------------
