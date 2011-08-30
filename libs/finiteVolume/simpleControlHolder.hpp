#ifndef simpleControlHolder_hpp
#define simpleControlHolder_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"
#include "Deps.hpp"
#include "fvMeshHolder.hpp"

#include <simpleControl.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class simpleControlHolder 
    : protected universalArgs
    , public boost::shared_ptr< simpleControl >
    , public universalHolder
  {
  public:
    simpleControlHolder( fvMeshHolder& mesh );
    ~simpleControlHolder();
    
    virtual universalHolder* clone() const;
    
    using  boost::shared_ptr< simpleControl >::operator*;
    using  boost::shared_ptr< simpleControl >::operator->;

  private:
    simpleControlHolder(); // not implemented
    //simpleControlHolder( const simpleControlHolder& ); // not implemented
    void operator=( const simpleControlHolder& ); // not implemented

  };
} // Foam


//---------------------------------------------------------------------------
#endif
