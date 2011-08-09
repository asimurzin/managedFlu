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
  class surfaceVectorFieldHolder ;
  class surfaceScalarFieldHolder;
  class volVectorFieldHolder;
  
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

    //redefine some functions which returns holders
    const surfaceVectorFieldHolder Sf() const;
    const surfaceScalarFieldHolder magSf() const;
    const surfaceScalarFieldHolder phi() const;
    const volVectorFieldHolder C() const;
    const surfaceVectorFieldHolder Cf() const;

  private:
    fvMeshHolder(); // not implemented
    // fvMeshHolder( const fvMeshHolder& ); // not implemented 
    void operator = ( const fvMeshHolder& ); // not implemented 
  };

} // Foam


//---------------------------------------------------------------------------
#endif
