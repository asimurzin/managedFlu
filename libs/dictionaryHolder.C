#ifndef dictionaryHolder_C
#define dictionaryHolder_C


//---------------------------------------------------------------------------
#include "dictionaryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  dictionaryHolder::dictionaryHolder( const boost::shared_ptr< dictionary >& dict ): boost::shared_ptr< dictionary >( dict )
  {}

  dictionaryHolder::dictionaryHolder(): boost::shared_ptr< dictionary >( new dictionary() )
  {}

}//Foam


//---------------------------------------------------------------------------
#endif
