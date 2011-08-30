#ifndef basicPsiThermoHolder_hpp
#define basicPsiThermoHolder_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "Deps.hpp"
#include "basicThermoHolder.hpp"
#include "fvMeshHolder.hpp"

#include <basicPsiThermo.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class basicPsiThermoHolder 
    : virtual protected universalArgs
    , public boost::shared_ptr< basicPsiThermo >
    , public basicThermoHolder
  {
  public:
    basicPsiThermoHolder( const boost::shared_ptr< basicPsiThermo >&, const fvMeshHolder& );
    basicPsiThermoHolder();
    
    ~basicPsiThermoHolder();

    static basicPsiThermoHolder New( const fvMeshHolder& );
    
    virtual universalHolder* clone() const;
    
    using  boost::shared_ptr< basicPsiThermo >::operator*;
    using  boost::shared_ptr< basicPsiThermo >::operator->;
  };
} // Foam


//---------------------------------------------------------------------------
#endif
