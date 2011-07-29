#ifndef fvMeshArgs_H
#define fvMeshArgs_H


//---------------------------------------------------------------------------
#include "surfaceInterpolationArgs.H"
#include "IOobjectHolder.H"
#include "polyMeshArgs.H"
#include "dataArgs.H"
#include "fvSchemesArgs.H"
#include "fvSolutionArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshArgs 
       : protected IOobjectHolder
       , private surfaceInterpolationArgs
       , private polyMeshArgs
       , private dataArgs
       , private fvSchemesArgs
       , private fvSolutionArgs
  {
  protected:
    fvMeshArgs( const IOobjectHolder& orh );
    fvMeshArgs();
  private:
    // fvMeshArgs(); // not implemented
    fvMeshArgs( const fvMeshArgs& ); // not implemented 
    void operator = ( const fvMeshArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
