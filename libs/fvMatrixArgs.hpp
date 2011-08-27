#ifndef fvMatrixArgs_hpp
#define fvMatrixArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "volFields.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
  
  class fvMatrixArgs
    : public universalArgs  
  {
  public:
    fvMatrixArgs( const universalHolder* );
    fvMatrixArgs( const std::set< holderPtr >& );
    
  protected:
    fvMatrixArgs();
  private:
    // fvMatrixArgs( const fvMatrixArgs& ); // not implemented 
    //void operator = ( const fvMatrixArgs& ); // not implemented 
    //fvMatrixArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#include "fvMatrixArgs.cpp"


//---------------------------------------------------------------------------
#endif
