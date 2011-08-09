#ifndef surfaceScalarFieldArgs_H
#define surfaceScalarFieldArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class surfaceScalarFieldArgs
  {
  public:
    const fvMeshHolder& get_fvMeshArg() const;
  protected:
    surfaceScalarFieldArgs( const fvMeshHolder& r);
  private:
    boost::shared_ptr< fvMeshHolder > fvMeshArg;
    //surfaceScalarFieldArgs( const surfaceScalarFieldArgs& ); // not implemented 
    //void operator = ( const surfaceScalarFieldArgs& ); // not implemented 
    surfaceScalarFieldArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
