#ifndef RASModelHolder_010701_hpp
#define RASModelHolder_010701_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "turbulenceModels/compressible/turbulenceModelHolder.hpp"

#include <compressible/RAS/RASModel/RASModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class RASModelHolder 
    : public turbulenceModelHolder
    , public boost::shared_ptr< RASModel >
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
      const basicThermoHolder& );

    virtual SimpleHolder* clone() const;
    
    ~RASModelHolder();
    
    using  boost::shared_ptr< RASModel >::operator*;
    using  boost::shared_ptr< RASModel >::operator->;

  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
