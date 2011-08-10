#ifndef fvScalarMatrixHolder_H
#define fvScalarMatrixHolder_H


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include <tmp.H>
#include "fvScalarMatrixArgs.H"
#include "surfaceFieldsMM.H"
#include "volFieldsMM.H"

//---------------------------------------------------------------------------
namespace Foam
{

  class fvScalarMatrixHolder : 
    public fvScalarMatrixArgs, 
    public tmp< fvScalarMatrix >
  {
  public:
    fvScalarMatrixHolder( const tmp< fvScalarMatrix >& , const volScalarFieldHolder& );
    ~fvScalarMatrixHolder();
    
    volScalarFieldHolder A() const
    {
      return  volScalarFieldHolder( operator()().A(), get_fvMeshArg() );
    }
    volScalarFieldHolder H() const
    {
      return  volScalarFieldHolder( operator()().H(), get_fvMeshArg() );
    }
    volScalarFieldHolder H1() const
    {
      return  volScalarFieldHolder( operator()().H1(), get_fvMeshArg() );
    }
    surfaceScalarFieldHolder flux() const
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
