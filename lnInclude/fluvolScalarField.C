#ifndef fluvolScalarField_C
#define fluvolScalarField_C


//---------------------------------------------------------------------------
#include "fluvolScalarField.H"
#include <tmp.H>


//---------------------------------------------------------------------------
Foam::fluvolScalarField::fluvolScalarField( const IOobjectHolder& io, const fvMeshHolder& mesh ) : 
  fvMeshHolder( mesh ),
  volScalarField( *io, *mesh )
{
  cout << "fluvolScalarField = " << this << nl;
}

Foam::fluvolScalarField::fluvolScalarField( const Foam::tmp< Foam::volScalarField >& field, const fvMeshHolder& mesh ) : 
  fvMeshHolder( mesh ),
  volScalarField( field )
{
  
}

Foam::fluvolScalarField::~fluvolScalarField()
{
  cout << "~fluvolScalarField = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
