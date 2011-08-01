#ifndef volScalarFieldHolder_C
#define volScalarFieldHolder_C


//---------------------------------------------------------------------------
#include "volScalarFieldHolder.H"
#include "fluvolScalarField.H"

//---------------------------------------------------------------------------
Foam::volScalarFieldHolder::volScalarFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
  boost::shared_ptr< volScalarField >( new fluvolScalarField( io, mesh ) )
{}


//---------------------------------------------------------------------------
#endif
