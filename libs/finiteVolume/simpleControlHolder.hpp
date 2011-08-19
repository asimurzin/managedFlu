#ifndef simpleControlHolder_hpp
#define simpleControlHolder_hpp


//---------------------------------------------------------------------------
#include "simpleControlArgs.hpp"
#include "fvMeshHolder.hpp"

#include <simpleControl.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class simpleControlHolder 
    : public simpleControlArgs
    , public boost::shared_ptr< simpleControl >
  {
  public:
    simpleControlHolder( fvMeshHolder& mesh );
    ~simpleControlHolder();

    using  boost::shared_ptr< simpleControl >::operator*;
    using  boost::shared_ptr< simpleControl >::operator->;

  private:
    simpleControlHolder(); // not implemented
    simpleControlHolder( const simpleControlHolder& ); // not implemented
    void operator=( const simpleControlHolder& ); // not implemented

  };
} // Foam


//---------------------------------------------------------------------------
#endif
