#ifndef fvMeshHolder_C
#define fvMeshHolder_C


//---------------------------------------------------------------------------
#include "fvMeshHolder.H"
#include "flufvMesh.H"


//---------------------------------------------------------------------------
Foam::fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) : 
  boost::shared_ptr< fvMesh >( new flufvMesh( io ) ),
  objectRegistryHolder( boost::shared_ptr< fvMesh >( *this ) )
{}

Foam::fvMeshHolder::fvMeshHolder( const boost::shared_ptr< fvMesh >&  t ) : 
  boost::shared_ptr< fvMesh >( t ),
  objectRegistryHolder( t )
{} 

Foam::fvMeshHolder::fvMeshHolder() : 
  boost::shared_ptr< fvMesh >(),
  objectRegistryHolder()
{} 


//---------------------------------------------------------------------------
#endif
