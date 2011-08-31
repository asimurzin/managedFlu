#ifndef compressibleRASModelHolder_hpp
#define compressibleRASModelHolder_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "turbulenceModelHolder.hpp"

#include <compressible/RAS/RASModel/RASModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class RASModelHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< RASModel >
    , public turbulenceModelHolder
  {
  public:
    RASModelHolder( 
      const boost::shared_ptr< RASModel >&, 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder& );

    RASModelHolder();
    
    static RASModelHolder New( 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder&,
      const word& turbulenceModelName = turbulenceModel::typeName );

    virtual universalHolder* clone() const;
    
    ~RASModelHolder();
    
    using  boost::shared_ptr< RASModel >::operator*;
    using  boost::shared_ptr< RASModel >::operator->;

  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
