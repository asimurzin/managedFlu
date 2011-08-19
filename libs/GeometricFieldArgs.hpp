#ifndef GeometricFieldArgs_hpp
#define GeometricFieldArgs_hpp


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class GeometricFieldArgs
  {
  public:
    fvMeshHolder mesh() const;

  protected:
    GeometricFieldArgs( const fvMeshHolder&);
    GeometricFieldArgs();
    
  private:
    boost::shared_ptr< fvMeshHolder > mesh_;

  private:
//   GeometricFieldArgs( const GeometricFieldArgs& ); // not implemented 
//   void operator = ( const GeometricFieldArgs& ); // not implemented 
//   GeometricFieldArgs(); //not implemented

  };
} // Foam


//---------------------------------------------------------------------------
#endif
