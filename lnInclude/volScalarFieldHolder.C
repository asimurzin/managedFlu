#ifndef volScalarFieldHolder_C
#define volScalarFieldHolder_C


//---------------------------------------------------------------------------
#include "volScalarFieldHolder.H"
#include "fluvolScalarField.H"

//---------------------------------------------------------------------------
namespace Foam
{
//Constructors
  volScalarFieldHolder::volScalarFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
    fvMeshHolder( mesh ),
    boost::shared_ptr< volScalarField >( new volScalarField( *io, *mesh ) )
  {
    cout << "fluvolScalarField = " << this << nl;
  }

  volScalarFieldHolder::volScalarFieldHolder( volScalarField* gf, const fvMeshHolder& mesh ) : 
    fvMeshHolder( mesh ), 
    boost::shared_ptr< volScalarField >( gf )
  {
    cout << "fluvolScalarField = " << this << nl;
  }


  volScalarFieldHolder::~volScalarFieldHolder()
  {
    cout << "~fluvolScalarField = " << this << nl;
  }


//---------------------------------------------------------------------------
   volScalarFieldHolder operator+ ( const volScalarFieldHolder& field1, const volScalarFieldHolder& field2 )
   {
     return volScalarFieldHolder( ( *field1 + *field2 ).ptr() , field1 );
   }


//---------------------------------------------------------------------------
} //Foam


//---------------------------------------------------------------------------
#endif
