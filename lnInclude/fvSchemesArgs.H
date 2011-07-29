#ifndef fvSchemesArgs_H
#define fvSchemesArgs_H


//---------------------------------------------------------------------------
#include "IOdictionaryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class fvSchemesArgs 
       : protected IOdictionaryArgs
  {
  protected:
    fvSchemesArgs();
    fvSchemesArgs( const IOobjectHolder& io );
  private:
    // fvSchemesArgs(); // not implemented
    fvSchemesArgs( const fvSchemesArgs& ); // not implemented 
    void operator = ( const fvSchemesArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
