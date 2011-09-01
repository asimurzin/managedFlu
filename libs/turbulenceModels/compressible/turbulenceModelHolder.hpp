#ifndef compressibleturbulenceModelHolder_hpp
#define compressibleturbulenceModelHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "volFields.hpp"
#include "basicThermoHolder.hpp"


#include <compressible/turbulenceModel/turbulenceModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
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

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
