//---------------------------------------------------------------------------
#include "basicThermoArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  basicThermoArgs::basicThermoArgs( const fvMeshHolder& mesh ) 
    : mesh_( new fvMeshHolder( mesh ) )
  {}

  fvMeshHolder basicThermoArgs::mesh() const
  {
    return *mesh_;
  }
}


//---------------------------------------------------------------------------
