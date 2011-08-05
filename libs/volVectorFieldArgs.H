#ifndef volVectorFieldArgs_H
#define volVectorFieldArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class volVectorFieldArgs
  {
  public:
    const fvMeshHolder& get_fvMeshArg() const;
  protected:
    volVectorFieldArgs( const fvMeshHolder& r);
  private:
    boost::shared_ptr< fvMeshHolder > fvMeshArg;
    //volVectorFieldArgs( const volVectorFieldArgs& ); // not implemented 
    void operator = ( const volVectorFieldArgs& ); // not implemented 
    volVectorFieldArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
