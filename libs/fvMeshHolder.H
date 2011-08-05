#ifndef fvMeshHolder_H
#define fvMeshHolder_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include <boost/shared_ptr.hpp>
#include "fvMeshArgs.H"
#include "objectRegistryHolder.H"

//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  
  class fvMeshHolder : 
    protected fvMeshArgs
    , public boost::shared_ptr< fvMesh >
    , public objectRegistryHolder
    , public IOobjectHolder
  {
  public:
    fvMeshHolder( const IOobjectHolder& io );
    using boost::shared_ptr< fvMesh >::operator*;
    using boost::shared_ptr< fvMesh >::operator->;
    ~fvMeshHolder();
  private:
    fvMeshHolder(); // not implemented
    // fvMeshHolder( const fvMeshHolder& ); // not implemented 
    void operator = ( const fvMeshHolder& ); // not implemented 
  };

} // Foam


//---------------------------------------------------------------------------
#endif
