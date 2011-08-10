#ifndef fvVectorMatrixHolder_H
#define fvVectorMatrixHolder_H


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include <tmp.H>
#include "fvVectorMatrixArgs.H"
#include "surfaceFieldsMM.H"
#include "volFieldsMM.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class fvVectorMatrixHolder 
    : public fvVectorMatrixArgs
    , public tmp< fvVectorMatrix >
  {
  public:
    fvVectorMatrixHolder( const tmp< fvVectorMatrix >& , const volVectorFieldHolder& );
    ~fvVectorMatrixHolder();

    // re-define functions which returns "holders"
    volScalarFieldHolder A() const
    {
      return  volScalarFieldHolder( operator()().A(), get_fvMeshArg() );
    }
    volVectorFieldHolder H() const
    {
      return  volVectorFieldHolder( operator()().H(), get_fvMeshArg() );
    }
    
    volScalarFieldHolder H1() const
    {
      return  volScalarFieldHolder( operator()().H1(), get_fvMeshArg() );
    }
    surfaceVectorFieldHolder flux() const
    {
      return  surfaceVectorFieldHolder( operator()().flux(), get_fvMeshArg() );
    }
    
  private:
    fvVectorMatrixHolder(); // not implemented
    // fvVectorMatrixHolder( const fvVectorMatrixHolder& ); // not implemented 
    void operator = ( const fvVectorMatrixHolder& ); // not implemented 
  };
  
  fvVectorMatrixHolder operator + ( const fvVectorMatrixHolder&, const fvVectorMatrixHolder& );
  fvVectorMatrixHolder operator - ( const fvVectorMatrixHolder&, const fvVectorMatrixHolder& );
} // Foam


//---------------------------------------------------------------------------
#endif
