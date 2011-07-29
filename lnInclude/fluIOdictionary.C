#ifndef fluIOdictionary_C
#define fluIOdictionary_C


//---------------------------------------------------------------------------
#include "fluIOdictionary.H"


//---------------------------------------------------------------------------
Foam::fluIOdictionary::fluIOdictionary( const IOobjectHolder& io ) : IOdictionaryArgs( io ),
                                                                     IOdictionary( *io )
{
  cout << "fluIOdictionary = " << this << nl;
}

Foam::fluIOdictionary::~fluIOdictionary()
{
  cout << "~fluIOdictionary = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
