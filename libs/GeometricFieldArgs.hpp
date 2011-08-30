#ifndef GeometricFieldArgs_hpp
#define GeometricFieldArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "Deps.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class GeometricFieldArgs
    : public universalArgs
  {
  public:
    GeometricFieldArgs( const Deps& );

  protected:
    GeometricFieldArgs();
    
  private:
//   GeometricFieldArgs( const GeometricFieldArgs& ); // not implemented 
//   void operator = ( const GeometricFieldArgs& ); // not implemented 
//   GeometricFieldArgs(); //not implemented

  };
} // Foam


//---------------------------------------------------------------------------
#endif
