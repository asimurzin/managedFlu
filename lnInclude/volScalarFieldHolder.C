#ifndef volScalarFieldHolder_C
#define volScalarFieldHolder_C


//---------------------------------------------------------------------------
#include "volScalarFieldHolder.H"
#include "fluvolScalarField.H"

//---------------------------------------------------------------------------
Foam::volScalarFieldHolder::volScalarFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
  boost::shared_ptr< fluvolScalarField >( new fluvolScalarField( io, mesh ) )
{}

Foam::volScalarFieldHolder::volScalarFieldHolder( const boost::shared_ptr< fluvolScalarField >& t ) :
  boost::shared_ptr< fluvolScalarField >( t )
{}


namespace Foam
{
 volScalarFieldHolder operator+ ( const volScalarFieldHolder& field1, const volScalarFieldHolder& field2 )
 {
   return volScalarFieldHolder( boost::shared_ptr< fluvolScalarField >( new fluvolScalarField( *field1 + *field2 , fvMeshHolder( *field1 ) ) ) );
 }
}

//---------------------------------------------------------------------------
#endif
