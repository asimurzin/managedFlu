#ifndef fvMeshHolder_C
#define fvMeshHolder_C


//---------------------------------------------------------------------------
#include "fvMeshHolder.H"
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) : 
    fvMeshArgs( io ),
    boost::shared_ptr< fvMesh >( new fvMesh( *io ) ),
    objectRegistryHolder( io ),
    IOobjectHolder( io )
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
#endif
