#ifndef fvVectorMatrixHolder_H
#define fvVectorMatrixHolder_H


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include <tmp.H>
#include "fvVectorMatrixArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class volVectorFieldHolder;
  
  class fvVectorMatrixHolder : 
    public fvVectorMatrixArgs, 
    public tmp< fvVectorMatrix >
  {
  public:
    fvVectorMatrixHolder( const tmp< fvVectorMatrix >& , const volVectorFieldHolder& );
    ~fvVectorMatrixHolder();
  private:
     fvVectorMatrixHolder(); // not implemented
    // fvVectorMatrixHolder( const fvVectorMatrixHolder& ); // not implemented 
     void operator = ( const fvVectorMatrixHolder& ); // not implemented 
  };
  
  fvVectorMatrixHolder operator+ ( const fvVectorMatrixHolder&, const fvVectorMatrixHolder& );
  fvVectorMatrixHolder operator- ( const fvVectorMatrixHolder&, const fvVectorMatrixHolder& );

} // Foam


//---------------------------------------------------------------------------
#endif
