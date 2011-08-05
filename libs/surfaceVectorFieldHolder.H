#ifndef surfaceVectorFieldHolder_H
#define surfaceVectorFieldHolder_H


//---------------------------------------------------------------------------
#include <surfaceFields.H>
#include <tmp.H>
#include "surfaceVectorFieldArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  class surfaceScalarFieldHolder;
  
  class surfaceVectorFieldHolder : 
    public surfaceVectorFieldArgs, 
    public tmp< surfaceVectorField >
  {
  public:
    surfaceVectorFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    surfaceVectorFieldHolder( const tmp< surfaceVectorField >& , const fvMeshHolder& );
    ~surfaceVectorFieldHolder();
  private:
     surfaceVectorFieldHolder(); // not implemented
    // surfaceVectorFieldHolder( const surfaceVectorFieldHolder& ); // not implemented 
     void operator = ( const surfaceVectorFieldHolder& ); // not implemented 
  };
  
  surfaceVectorFieldHolder operator+ ( const surfaceVectorFieldHolder&, const surfaceVectorFieldHolder& );
  surfaceScalarFieldHolder operator& ( const surfaceVectorFieldHolder&, const surfaceVectorField& );

} // Foam


//---------------------------------------------------------------------------
#endif
