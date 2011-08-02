#ifndef volScalarFieldHolder_H
#define volScalarFieldHolder_H


//---------------------------------------------------------------------------
#include "fluvolScalarField.H"
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  class fvMeshHolder;
  
  class volScalarFieldHolder : public boost::shared_ptr< fluvolScalarField >
  {
  public:
    volScalarFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    
    volScalarFieldHolder( const boost::shared_ptr< fluvolScalarField >& );
  private:
     volScalarFieldHolder(); // not implemented
    // volScalarFieldHolder( const volScalarFieldHolder& ); // not implemented 
     void operator = ( const volScalarFieldHolder& ); // not implemented 
  };
  volScalarFieldHolder operator+ ( const volScalarFieldHolder&, const volScalarFieldHolder& );
} // Foam


//---------------------------------------------------------------------------
#endif
