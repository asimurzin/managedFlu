#ifndef flufvMesh_H
#define flufvMesh_H


//---------------------------------------------------------------------------
#include <fvMesh.H>
#include "IOobjectHolder.H"

namespace Foam
{
  class flufvMesh : public IOobjectHolder, public fvMesh
  {
  private:
    flufvMesh( const IOobjectHolder& io ) : IOobjectHolder( io ),
                                            fvMesh( *io )
    {}
    flufvMesh( const flufvMesh& ); // not implemented
    flufvMesh(); // not implemented
    friend class fvMeshHolder;
  };
} // Foam

#endif
