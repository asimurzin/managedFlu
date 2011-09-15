#ifndef incompressibleRASModelHolder_020000_hpp
#define incompressibleRASModelHolder_020000_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "incompressibleTurbulenceModelHolder.hpp"
#include "transportModelHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


#include <incompressible/RAS/RASModel/RASModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace incompressible
{
  class RASModelHolder 
    : public turbulenceModelHolder
    , public boost::shared_ptr< RASModel >
  {
  public:
    RASModelHolder( 
      const boost::shared_ptr< RASModel >&, 
      const volVectorFieldHolder&,
      const surfaceScalarFieldHolder&,
      transportModelHolder& );

    RASModelHolder();
    
    static RASModelHolder New( 
      const volVectorFieldHolder& U,
      const surfaceScalarFieldHolder& phi,
      transportModelHolder& transport,
      const word& turbulenceModelName = turbulenceModel::typeName );

    virtual SimpleHolder* clone() const;
    
    ~RASModelHolder();
    
    using  boost::shared_ptr< RASModel >::operator*;
    using  boost::shared_ptr< RASModel >::operator->;

  };

} //incompressible
} // Foam


//---------------------------------------------------------------------------
#endif
