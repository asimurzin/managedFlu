#ifndef basicRhoThermoHolder_hpp
#define basicRhoThermoHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "basicThermoHolder.hpp"
#include "fvMeshHolder.hpp"

#include <basicRhoThermo.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class basicRhoThermoHolder 
    : public basicThermoHolder
    , public boost::shared_ptr< basicRhoThermo >
  {
  public:
    basicRhoThermoHolder( const boost::shared_ptr< basicRhoThermo >&, const fvMeshHolder& );
    basicRhoThermoHolder();
    
    ~basicRhoThermoHolder();

    static basicRhoThermoHolder New( const fvMeshHolder& );
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< basicRhoThermo >::operator*;
    using  boost::shared_ptr< basicRhoThermo >::operator->;
  };
} // Foam


//---------------------------------------------------------------------------
#endif
