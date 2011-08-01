#ifndef volScalarFieldHolder_H
#define volScalarFieldHolder_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  class fvMeshHolder;
  
  class volScalarFieldHolder : public boost::shared_ptr< volScalarField >
  {
  public:
    volScalarFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh );
  protected:
    volScalarFieldHolder( const boost::shared_ptr< volScalarField >&  t );
  private:
     volScalarFieldHolder(); // not implemented
    // volScalarFieldHolder( const volScalarFieldHolder& ); // not implemented 
     void operator = ( const volScalarFieldHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
