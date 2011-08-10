#ifndef GeometricFieldArgs_H
#define GeometricFieldArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class GeometricFieldArgs
  {
  public:
    const fvMeshHolder& mesh() const;

  protected:
    GeometricFieldArgs( const fvMeshHolder& r);

  private:
    boost::shared_ptr< fvMeshHolder > mesh_;

  private:
    // GeometricFieldArgs( const GeometricFieldArgs& ); // not implemented 
    void operator = ( const GeometricFieldArgs& ); // not implemented 
    GeometricFieldArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
