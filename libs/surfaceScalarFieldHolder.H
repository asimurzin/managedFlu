#ifndef surfaceScalarFieldHolder_H
#define surfaceScalarFieldHolder_H


//---------------------------------------------------------------------------
#include <surfaceFields.H>
#include <tmp.H>
#include "surfaceScalarFieldArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  class surfaceScalarFieldHolder : 
    public surfaceScalarFieldArgs, 
    public tmp< surfaceScalarField >
  {
  public:
    surfaceScalarFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    surfaceScalarFieldHolder( const IOobjectHolder&, const surfaceScalarFieldHolder& );
    surfaceScalarFieldHolder( const tmp< surfaceScalarField >& , const fvMeshHolder& );
    ~surfaceScalarFieldHolder();
  private:
     surfaceScalarFieldHolder(); // not implemented
    // surfaceScalarFieldHolder( const surfaceScalarFieldHolder& ); // not implemented 
     void operator = ( const surfaceScalarFieldHolder& ); // not implemented 
  };
  

} // Foam


//---------------------------------------------------------------------------
#endif
