#ifndef compressibleturbulenceModelHolder_hpp
#define compressibleturbulenceModelHolder_hpp


//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp" 
#include "universalHolder.hpp"

#include <compressible/turbulenceModel/turbulenceModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class turbulenceModelHolder 
    : protected turbulenceModelArgs
    , public boost::shared_ptr< turbulenceModel >
    , public universalHolder
  {
  public:
    turbulenceModelHolder( 
      const boost::shared_ptr< turbulenceModel >&, 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder& );

    turbulenceModelHolder();
    
    ~turbulenceModelHolder();
    
    virtual universalHolder* clone() const;
    
    using  boost::shared_ptr< turbulenceModel >::operator*;
    using  boost::shared_ptr< turbulenceModel >::operator->;

  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
