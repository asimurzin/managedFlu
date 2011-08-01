#ifndef flufvMesh_H
#define flufvMesh_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include "IOobjectHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class flufvMesh : 
    protected IOobjectHolder
    , public fvMesh
  {
  private:
    flufvMesh( const IOobjectHolder& io );
    flufvMesh( const flufvMesh& ); // not implemented
    flufvMesh(); // not implemented
    friend class fvMeshHolder;
  public:
    ~flufvMesh();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
