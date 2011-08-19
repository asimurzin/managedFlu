//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"

#include "IOobjectHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) 
    : fvMeshArgs( io )
    , boost::shared_ptr< fvMesh >( new fvMesh( *io ) )
    , objectRegistryHolder( io )
    , IOobjectHolder( io )
  {
#ifdef OUR_DEBUG  
    cout << "fvMeshHolder=" << this << nl;
#endif
  }

 fvMeshHolder::fvMeshHolder()
    : fvMeshArgs()
    , boost::shared_ptr< fvMesh >()
    , objectRegistryHolder()
    , IOobjectHolder()
  {
#ifdef OUR_DEBUG
    cout << "fvMeshHolder=" << this << nl;
#endif
  }

  fvMeshHolder::~fvMeshHolder()
  {
#ifdef OUR_DEBUG
    cout << "~fvMeshHolder=" << this << nl;
#endif
  }
} //Foam


//---------------------------------------------------------------------------
