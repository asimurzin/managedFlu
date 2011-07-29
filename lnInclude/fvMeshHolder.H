#ifndef fvMeshHolder_H
#define fvMeshHolder_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include <boost/shared_ptr.hpp>
#include "IOobjectHolder.H"
#include "objectRegistryHolder.H"


namespace Foam
{
  class fvMeshHolder : 
       public boost::shared_ptr< fvMesh >, 
       protected objectRegistryHolder
  {
  public:
    fvMeshHolder( const IOobjectHolder& io );
  protected:
    fvMeshHolder( const boost::shared_ptr< fvMesh >&  t );
    fvMeshHolder(); // not implemented
  private:
    // fvMeshHolder( const fvMeshHolder& ); // not implemented 
    void operator = ( const fvMeshHolder& ); // not implemented 
  public:
    using boost::shared_ptr<fvMesh>::operator*;
  };
} // Foam

#endif
