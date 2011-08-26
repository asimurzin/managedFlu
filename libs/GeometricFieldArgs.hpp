#ifndef GeometricFieldArgs_hpp
#define GeometricFieldArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class GeometricFieldArgs
    : universalArgs
  {
  public:
    const boost::shared_ptr< fvMeshHolder >& mesh() const;

    GeometricFieldArgs( const fvMeshHolder&);
    GeometricFieldArgs( const universalArgs&);

  protected:
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
