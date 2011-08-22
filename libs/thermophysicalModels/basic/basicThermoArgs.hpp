#ifndef basicThermoArgs_hpp
#define basicThermoArgs_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class basicThermoArgs
  {
  public:
    fvMeshHolder  mesh() const ;

  protected:
    basicThermoArgs( const fvMeshHolder& );
    
  private:
    boost::shared_ptr< fvMeshHolder > mesh_;
    
    basicThermoArgs(); // not implemented
    //basicThermoArgs( const basicThermoArgs& ); // not implemented 
    void operator=( const basicThermoArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
