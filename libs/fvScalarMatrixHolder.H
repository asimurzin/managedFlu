#ifndef fvScalarMatrixHolder_H
#define fvScalarMatrixHolder_H


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include <tmp.H>
#include "fvScalarMatrixArgs.H"
#include "volScalarFieldHolder.H"
#include "surfaceScalarFieldHolder.H"

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
    
    inline volScalarFieldHolder A() const
    {
      return  volScalarFieldHolder( operator()().A(), get_fvMeshArg() );
    }
    inline volScalarFieldHolder H() const
    {
      return  volScalarFieldHolder( operator()().H(), get_fvMeshArg() );
    }

    inline volScalarFieldHolder H1() const
    {
      return  volScalarFieldHolder( operator()().H1(), get_fvMeshArg() );
    }
    inline surfaceScalarFieldHolder flux() const
    {
      return  surfaceScalarFieldHolder( operator()().flux(), get_fvMeshArg() );
    }
  private:
     fvScalarMatrixHolder(); // not implemented
    // fvScalarMatrixHolder( const fvScalarMatrixHolder& ); // not implemented 
     void operator = ( const fvScalarMatrixHolder& ); // not implemented 
  };
  
} // Foam


//---------------------------------------------------------------------------
#endif
