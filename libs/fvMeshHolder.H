#ifndef fvMeshHolder_H
#define fvMeshHolder_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include <boost/shared_ptr.hpp>
#include "fvMeshArgs.H"
#include "objectRegistryHolder.H"
#include "volFieldsFwdMM.H"
#include "surfaceFieldsFwd.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  
  class fvMeshHolder 
    : protected fvMeshArgs
    , public boost::shared_ptr< fvMesh >
    , public objectRegistryHolder
    , public IOobjectHolder
  {
  public:
    fvMeshHolder( const IOobjectHolder& io );
    ~fvMeshHolder();

    using boost::shared_ptr< fvMesh >::operator*;
    using boost::shared_ptr< fvMesh >::operator->;

    //redefine some functions which returns holders
    surfaceVectorFieldHolder Sf() const;
    surfaceScalarFieldHolder magSf() const;
    surfaceScalarFieldHolder phi() const;
    volVectorFieldHolder C() const;
    surfaceVectorFieldHolder Cf() const;

  private:
    fvMeshHolder(); // not implemented
    // fvMeshHolder( const fvMeshHolder& ); // not implemented 
    void operator = ( const fvMeshHolder& ); // not implemented 
  };

} // Foam


//---------------------------------------------------------------------------
#endif
