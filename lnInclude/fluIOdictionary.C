#ifndef fluIOdictionary_C
#define fluIOdictionary_C


//---------------------------------------------------------------------------
#include "fluIOdictionary.H"


//---------------------------------------------------------------------------
Foam::fluIOdictionary::fluIOdictionary( const IOobjectHolder& io ) : 
  IOobjectHolder( io ),
  dictionaryHolder(), // initialized by null (  static dictionary null   from Foam::dictionary )
  IOdictionary( *io )
{
  cout << "fluIOdictionary = " << this << nl;
}

Foam::fluIOdictionary::fluIOdictionary( const IOobjectHolder& io, const dictionaryHolder& dh ) :
  IOobjectHolder( io ),
  dictionaryHolder( dh ), 
  IOdictionary( *io, *dh )
{}

Foam::fluIOdictionary::~fluIOdictionary()
{
  cout << "~fluIOdictionary = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
