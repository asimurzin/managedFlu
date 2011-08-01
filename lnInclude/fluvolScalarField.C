#ifndef fluvolScalarField_C
#define fluvolScalarField_C


//---------------------------------------------------------------------------
#include "fluvolScalarField.H"


//---------------------------------------------------------------------------
Foam::fluvolScalarField::fluvolScalarField( const IOobjectHolder& io, const fvMeshHolder& mesh ) : 
  fvMeshHolder( mesh ),
  volScalarField( *io, *mesh )
{
  cout << "fluvolScalarField = " << this << nl;
}

Foam::fluvolScalarField::~fluvolScalarField()
{
  cout << "~fluvolScalarField = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
