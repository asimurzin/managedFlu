#ifndef fvSolutionArgs_H
#define fvSolutionArgs_H


//---------------------------------------------------------------------------
#include "IOdictionaryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class fvSolutionArgs 
       : protected IOdictionaryArgs
  {
  protected:
    fvSolutionArgs();
    fvSolutionArgs( const IOobjectHolder& io );
  private:
    // fvSolutionArgs(); // not implemented
    fvSolutionArgs( const fvSolutionArgs& ); // not implemented 
    void operator = ( const fvSolutionArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
