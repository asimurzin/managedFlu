#ifndef volScalarFieldHolder_H
#define volScalarFieldHolder_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include <tmp.H>
#include "volScalarFieldArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  class volScalarFieldHolder : 
    public volScalarFieldArgs, 
    public tmp< volScalarField >
  {
  public:
    volScalarFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    volScalarFieldHolder( const tmp< volScalarField >& , const fvMeshHolder& );
    ~volScalarFieldHolder();
  private:
     volScalarFieldHolder(); // not implemented
    // volScalarFieldHolder( const volScalarFieldHolder& ); // not implemented 
     void operator = ( const volScalarFieldHolder& ); // not implemented 
  };
  
} // Foam


//---------------------------------------------------------------------------
#endif
