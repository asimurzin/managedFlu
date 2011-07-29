#ifndef IOdictionaryArgs_H
#define IOdictionaryArgs_H


//---------------------------------------------------------------------------
#include "IOdictionaryHolder.H"
#include "dictionaryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class IOdictionaryArgs 
       : protected IOobjectHolder
       , protected dictionaryArgs
  {
  protected:
    IOdictionaryArgs();
    IOdictionaryArgs( const IOobjectHolder& io );
  private:
    // IOdictionaryArgs(); // not implemented
    // IOdictionaryArgs( const IOdictionaryArgs& ); // not implemented 
    void operator = ( const IOdictionaryArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
