#ifndef flufvMesh_H
#define flufvMesh_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include "fvMeshArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class flufvMesh : protected fvMeshArgs, public fvMesh
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
