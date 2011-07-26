#ifndef fvMeshHolder_H
#define fvMeshHolder_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include <boost/shared_ptr.hpp>
#include "IOobjectHolder.H"
#include "flufvMesh.H"


namespace Foam
{
  class fvMeshHolder : public boost::shared_ptr< fvMesh >
  {
  public:
    fvMeshHolder( const IOobjectHolder& io ) : boost::shared_ptr< fvMesh >( new flufvMesh( io ) )
    {}
  protected:
    fvMeshHolder( const boost::shared_ptr< fvMesh >&  t ) : boost::shared_ptr< fvMesh >( t )
    {} 
  private:
    fvMeshHolder(); // not implemented
    fvMeshHolder( const fvMeshHolder& ); // not implemented 
    void operator = ( const fvMeshHolder& ); // not implemented 
  };
} // Foam

#endif
