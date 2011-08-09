#ifndef surfaceVectorFieldArgs_H
#define surfaceVectorFieldArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class surfaceVectorFieldArgs
  {
  public:
    const fvMeshHolder& get_fvMeshArg() const;
  protected:
    surfaceVectorFieldArgs( const fvMeshHolder& r);
  private:
    boost::shared_ptr< fvMeshHolder > fvMeshArg;
    //surfaceVectorFieldArgs( const surfaceVectorFieldArgs& ); // not implemented 
    //void operator = ( const surfaceVectorFieldArgs& ); // not implemented 
    surfaceVectorFieldArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
