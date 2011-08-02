#ifndef fvMeshHolder_C
#define fvMeshHolder_C


//---------------------------------------------------------------------------
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) : 
    IOobjectHolder( io ),
    boost::shared_ptr< fvMesh >( new fvMesh( *io ) ),
    objectRegistryHolder( boost::shared_ptr< fvMesh >( *this ) )
  {}

  fvMeshHolder::fvMeshHolder() : 
    IOobjectHolder(),
    boost::shared_ptr< fvMesh >(),
    objectRegistryHolder()
  {} 

} //Foam


//---------------------------------------------------------------------------
#endif
