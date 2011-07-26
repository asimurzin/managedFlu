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
    {
      cout << "flufvMesh = " << this << nl;
    }
    flufvMesh( const flufvMesh& ); // not implemented
    flufvMesh(); // not implemented
    friend class fvMeshHolder;
  public:
    ~flufvMesh()
    {
      cout << "~flufvMesh = " << this << nl;
    }
  };
} // Foam

#endif
