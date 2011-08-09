#ifndef volScalarFieldArgs_H
#define volScalarFieldArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class volScalarFieldArgs
  {
  public:
    const fvMeshHolder& get_fvMeshArg() const;
  protected:
    volScalarFieldArgs( const fvMeshHolder& r);
  private:
    boost::shared_ptr< fvMeshHolder > fvMeshArg;
    //volScalarFieldArgs( const volScalarFieldArgs& ); // not implemented 
    //void operator = ( const volScalarFieldArgs& ); // not implemented 
    volScalarFieldArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
