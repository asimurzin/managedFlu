#ifndef volVectorFieldHolder_H
#define volVectorFieldHolder_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include <tmp.H>
#include "volVectorFieldArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  class volVectorFieldHolder : 
    public volVectorFieldArgs, 
    public tmp< volVectorField >
  {
  public:
    volVectorFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    volVectorFieldHolder( const tmp< volVectorField >& , const fvMeshHolder& );
    ~volVectorFieldHolder();
  private:
     volVectorFieldHolder(); // not implemented
    // volVectorFieldHolder( const volVectorFieldHolder& ); // not implemented 
     void operator = ( const volVectorFieldHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
