#ifndef fvMeshHolder_H
#define fvMeshHolder_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include <boost/shared_ptr.hpp>
#include "IOobjectHolder.H"
#include "objectRegistryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class fvMeshHolder : 
    public IOobjectHolder,
    public boost::shared_ptr< fvMesh >,
    public objectRegistryHolder
  {
  public:
    fvMeshHolder( const IOobjectHolder& io );
    using boost::shared_ptr<fvMesh>::operator*;

  private:
    fvMeshHolder(); // not implemented
    // fvMeshHolder( const fvMeshHolder& ); // not implemented 
    void operator = ( const fvMeshHolder& ); // not implemented 
  };

} // Foam


//---------------------------------------------------------------------------
#endif
