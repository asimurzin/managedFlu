#ifndef flufvMesh_C
#define flufvMesh_C


//---------------------------------------------------------------------------
#include "flufvMesh.H"


//---------------------------------------------------------------------------
Foam::flufvMesh::flufvMesh( const IOobjectHolder& io ) : IOobjectHolder( io ),
                                                         fvMesh( *io )
{
  cout << "flufvMesh = " << this << nl;
}

Foam::flufvMesh::~flufvMesh()
{
  cout << "~flufvMesh = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
