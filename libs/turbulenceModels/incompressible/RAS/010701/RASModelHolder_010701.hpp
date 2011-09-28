#ifndef RASModelHolder_010701_hpp
#define RASModelHolder_010701_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "turbulenceModelHolder.hpp"
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
      transportModelHolder& transport );

    virtual SimpleHolder* clone() const;
    
    ~RASModelHolder();
    
    using  boost::shared_ptr< RASModel >::operator*;
    using  boost::shared_ptr< RASModel >::operator->;

  };

} //incompressible
} // Foam


//---------------------------------------------------------------------------
#endif
