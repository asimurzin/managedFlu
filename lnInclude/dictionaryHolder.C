#ifndef dictionaryHolder_C
#define dictionaryHolder_C


//---------------------------------------------------------------------------
#include "dictionaryHolder.H"


//---------------------------------------------------------------------------
Foam::dictionaryHolder::dictionaryHolder():boost::shared_ptr< dictionary >()
{}

Foam::dictionaryHolder::dictionaryHolder( const boost::shared_ptr<Foam::dictionary>& obr ): boost::shared_ptr< dictionary >( obr )
{}


//---------------------------------------------------------------------------
#endif
