#ifndef fvMeshArgs_hpp
#define fvMeshArgs_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "universalArgs.hpp"
#include "universalHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
   
  class fvMeshArgs
    : public universalArgs
  {
  protected:
    fvMeshArgs();
  
    fvMeshArgs( const Deps& );
    
  };
} // Foam


//---------------------------------------------------------------------------
#endif

