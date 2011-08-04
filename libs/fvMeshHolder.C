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
    cout << "fvMeshHolder=" << this << nl;
  }

  fvMeshHolder::~fvMeshHolder()
  {
    cout << "~fvMeshHolder=" << this << nl;
  }

} //Foam


//---------------------------------------------------------------------------
#endif
