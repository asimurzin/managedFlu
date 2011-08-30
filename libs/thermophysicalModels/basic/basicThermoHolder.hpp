#ifndef basicThermoHolder_hpp
#define basicThermoHolder_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "universalHolder.hpp"
#include "universalArgs.hpp"
#include "Deps.hpp"

#include <basicThermo.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class basicThermoHolder 
    : virtual protected universalArgs
    , public boost::shared_ptr< basicThermo >
    , public universalHolder
  {
  public:
    basicThermoHolder( const boost::shared_ptr< basicThermo >&, const fvMeshHolder& );
    basicThermoHolder();
    
    ~basicThermoHolder();
    
    virtual universalHolder* clone() const;
    
    using  boost::shared_ptr< basicThermo >::operator*;
    using  boost::shared_ptr< basicThermo >::operator->;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
