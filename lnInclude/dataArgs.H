#ifndef dataArgs_H
#define dataArgs_H


//---------------------------------------------------------------------------
#include "IOdictionaryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class dataArgs 
       : protected IOdictionaryArgs
  {
  protected:
    dataArgs();
    dataArgs( const IOobjectHolder& io );
  private:
    // dataArgs(); // not implemented
    dataArgs( const dataArgs& ); // not implemented 
    void operator = ( const dataArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
