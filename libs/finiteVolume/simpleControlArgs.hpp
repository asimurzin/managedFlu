#ifndef simpleControlArgs_hpp
#define simpleControlArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "fvMeshHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class simpleControlArgs
    : universalArgs
  {
  public:
    const fvMeshHolder&  mesh() const ;

  protected:
    simpleControlArgs( const fvMeshHolder& );

  private:
    boost::shared_ptr< fvMeshHolder > mesh_;
    simpleControlArgs(); // not implemented
    simpleControlArgs( const simpleControlArgs& ); // not implemented 
    void operator=( const simpleControlArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
