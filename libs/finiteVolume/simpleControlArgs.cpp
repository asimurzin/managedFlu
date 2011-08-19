//---------------------------------------------------------------------------
#include "simpleControlArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  simpleControlArgs::simpleControlArgs( const fvMeshHolder& mesh ) 
    : mesh_( new fvMeshHolder( mesh ) )
  {}

  const fvMeshHolder& simpleControlArgs::mesh() const
  {
    return *mesh_;
  }
}


//---------------------------------------------------------------------------
