//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"

#include "IOobjectHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) 
    : DependentHolder( &io )
    , boost::shared_ptr< fvMesh >( new fvMesh( *io ) )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< fvMesh >( *this ) );
  }

  fvMeshHolder::fvMeshHolder( fvMesh* mesh, const Deps& the_deps ) 
    : DependentHolder( the_deps )
    , boost::shared_ptr< fvMesh >( mesh )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< fvMesh >( *this ) );
  }
  
  fvMeshHolder::fvMeshHolder()
    : DependentHolder()
    , boost::shared_ptr< fvMesh >()
  {}

  SimpleHolder* fvMeshHolder::clone() const
  {
    return new fvMeshHolder( *this );
  }
  
  fvMeshHolder::~fvMeshHolder()
  {}

} //Foam


//---------------------------------------------------------------------------
