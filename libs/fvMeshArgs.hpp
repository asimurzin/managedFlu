#ifndef fvMeshArgs_hpp
#define fvMeshArgs_hpp


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
   
  class fvMeshArgs
  {
  public:
    fvMeshArgs();
  
  protected:
    fvMeshArgs( const IOobjectHolder & registry );
    
  private:
    boost::shared_ptr< IOobjectHolder > IOobjectArg;

  private:
    // fvMeshArgs( const fvMeshArgs& ); // not implemented 
    //void operator = ( const fvMeshArgs& ); // not implemented 
    //fvMeshArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
