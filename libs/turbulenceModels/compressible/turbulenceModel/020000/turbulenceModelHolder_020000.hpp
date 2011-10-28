#ifndef turbulenceModelHolder_020000_hpp
#define turbulenceModelHolder_020000_hpp


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
    
    static turbulenceModelHolder New( const volScalarFieldHolder& rho,
                                      const volVectorFieldHolder& U,
                                      const surfaceScalarFieldHolder& phi,
                                      const basicThermoHolder& thermoPhysicalModel,
                                      const word& turbulenceModelName = turbulenceModel::typeName );
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< turbulenceModel >::operator*;
    using  boost::shared_ptr< turbulenceModel >::operator->;

  protected:
    turbulenceModelHolder( const boost::shared_ptr< turbulenceModel >& tm, 
                           const volScalarFieldHolder& rho,
                           const volVectorFieldHolder& U,
                           const surfaceScalarFieldHolder& phi, 
                           const basicThermoHolder& thermoPhysicalModel );
    void operator=( const boost::shared_ptr< turbulenceModel >& );
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
