#ifndef basicThermoHolder_hpp
#define basicThermoHolder_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"

#include <basicThermo.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class basicThermoHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< basicThermo >
  {
  public:
    basicThermoHolder( const boost::shared_ptr< basicThermo >&, const fvMeshHolder& );
    basicThermoHolder();
    
    ~basicThermoHolder();
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< basicThermo >::operator*;
    using  boost::shared_ptr< basicThermo >::operator->;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
