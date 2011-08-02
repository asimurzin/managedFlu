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
  
  class volScalarFieldHolder : public fvMeshHolder, public boost::shared_ptr< volScalarField >
  {
  public:
    volScalarFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    volScalarFieldHolder( volScalarField* , const fvMeshHolder& );
    using boost::shared_ptr< volScalarField >::operator->;
    using boost::shared_ptr< volScalarField >::operator*;
    ~volScalarFieldHolder();
  private:
     volScalarFieldHolder(); // not implemented
    // volScalarFieldHolder( const volScalarFieldHolder& ); // not implemented 
     void operator = ( const volScalarFieldHolder& ); // not implemented 
  };
  
  volScalarFieldHolder operator+ ( const volScalarFieldHolder&, const volScalarFieldHolder& );

} // Foam


//---------------------------------------------------------------------------
#endif
