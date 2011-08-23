#ifndef basicPsiThermoArgs_hpp
#define basicPsiThermoArgs_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "basicThermoArgs.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class basicPsiThermoArgs
  : basicThermoArgs
  {
  protected:
    basicPsiThermoArgs( const fvMeshHolder& );
  private:
    boost::shared_ptr< fvMeshHolder > mesh_;
    
    basicPsiThermoArgs(); // not implemented
    //basicPsiThermoArgs( const basicPsiThermoArgs& ); // not implemented 
    void operator=( const basicPsiThermoArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
