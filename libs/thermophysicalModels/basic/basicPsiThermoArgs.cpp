//---------------------------------------------------------------------------
#include "basicPsiThermoArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  basicPsiThermoArgs::basicPsiThermoArgs( const fvMeshHolder& mesh ) 
    : basicThermoArgs( mesh )
    , mesh_( new fvMeshHolder( mesh ) )
    
  {}

}


//---------------------------------------------------------------------------
