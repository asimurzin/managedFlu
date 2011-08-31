//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"

#include "IOobjectHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) 
    : DependentHolder( Foam::deps( &io ) )
    , boost::shared_ptr< fvMesh >( new fvMesh( *io ) )
    , objectRegistryHolder(  boost::shared_ptr< fvMesh >( *this ) )
  {
#ifdef OUR_DEBUG  
    cout << "fvMeshHolder=" << this << nl;
#endif
  }

 fvMeshHolder::fvMeshHolder()
    : DependentHolder()
    , boost::shared_ptr< fvMesh >()
    , objectRegistryHolder()
  {
#ifdef OUR_DEBUG
    cout << "fvMeshHolder=" << this << nl;
#endif
  }

  SimpleHolder* fvMeshHolder::clone() const
  {
    return new fvMeshHolder( *this );
  }
  
  fvMeshHolder::~fvMeshHolder()
  {
#ifdef OUR_DEBUG
    cout << "~fvMeshHolder=" << this << nl;
#endif
  }
} //Foam


//---------------------------------------------------------------------------
