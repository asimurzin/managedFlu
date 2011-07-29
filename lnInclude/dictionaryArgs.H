#ifndef dictionaryArgs_H
#define dictionaryArgs_H


//---------------------------------------------------------------------------
#include "dictionaryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class dictionaryArgs 
       : protected dictionaryHolder
  {
  protected:
    dictionaryArgs();
    dictionaryArgs( const dictionaryHolder& dh );
  private:
    // dictionaryArgs(); // not implemented
    // dictionaryArgs( const dictionaryArgs& ); // not implemented 
    void operator = ( const dictionaryArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
