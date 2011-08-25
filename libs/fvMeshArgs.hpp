#ifndef fvMeshArgs_hpp
#define fvMeshArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
   
  class fvMeshArgs
    : universalArgs
  {
  public:
    fvMeshArgs();
  
  protected:
    fvMeshArgs( const IOobjectHolder & registry );
    
  private:
    boost::shared_ptr< IOobjectHolder > IOobjectArg;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
