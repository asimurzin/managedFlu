//---------------------------------------------------------------------------
#include "common.hpp"
#if FOAM_VERSION( <, 020000 )
#define pimpleControlHolder_hpp
#endif


//---------------------------------------------------------------------------
#ifndef pimpleControlHolder_hpp
#define pimpleControlHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "fvMeshHolder.hpp"

#include <pimpleControl.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class pimpleControlHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< pimpleControl >
  {
  public:
    pimpleControlHolder( fvMeshHolder& mesh );
    ~pimpleControlHolder();
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< pimpleControl >::operator*;
    using  boost::shared_ptr< pimpleControl >::operator->;

  private:
    pimpleControlHolder(); // not implemented
    //pimpleControlHolder( const pimpleControlHolder& ); // not implemented
    void operator=( const pimpleControlHolder& ); // not implemented

  };
} // Foam


//---------------------------------------------------------------------------
#endif
