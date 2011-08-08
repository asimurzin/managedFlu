#ifndef fvScalarMatrixHolder_H
#define fvScalarMatrixHolder_H


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include <tmp.H>
#include "fvScalarMatrixArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class volScalarFieldHolder;
  
  class fvScalarMatrixHolder : 
    public fvScalarMatrixArgs, 
    public tmp< fvScalarMatrix >
  {
  public:
    fvScalarMatrixHolder( const tmp< fvScalarMatrix >& , const volScalarFieldHolder& );
    ~fvScalarMatrixHolder();
  private:
     fvScalarMatrixHolder(); // not implemented
    // fvScalarMatrixHolder( const fvScalarMatrixHolder& ); // not implemented 
     void operator = ( const fvScalarMatrixHolder& ); // not implemented 
  };
  
} // Foam


//---------------------------------------------------------------------------
#endif
