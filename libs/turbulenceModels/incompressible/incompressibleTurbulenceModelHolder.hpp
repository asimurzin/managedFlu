#ifndef incompressibleTurbulenceModelHolder_hpp
#define incompressibleTurbulenceModelHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <incompressible/turbulenceModel/turbulenceModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace incompressible
{
  class turbulenceModelHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< turbulenceModel >
  {
  public:
    turbulenceModelHolder();
    ~turbulenceModelHolder();
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< turbulenceModel >::operator*;
    using  boost::shared_ptr< turbulenceModel >::operator->;

  protected:
    void operator=( const boost::shared_ptr< turbulenceModel >& );
  };

} //incompressible
} // Foam


//---------------------------------------------------------------------------
#endif
