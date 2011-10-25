#ifndef LESModelHolder_020000_hpp
#define LESModelHolder_020000_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "turbulenceModelHolder.hpp"
#include "transportModelHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


#include <incompressible/LES/LESModel/LESModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace incompressible
{
  class LESModelHolder 
    : public turbulenceModelHolder
    , public boost::shared_ptr< LESModel >
  {
  public:
    LESModelHolder( 
      const boost::shared_ptr< LESModel >&, 
      const volVectorFieldHolder&,
      const surfaceScalarFieldHolder&,
      transportModelHolder& );

    LESModelHolder();
    
    static LESModelHolder New( 
      const volVectorFieldHolder& U,
      const surfaceScalarFieldHolder& phi,
      transportModelHolder& transport,
      const word& turbulenceModelName = turbulenceModel::typeName );

    virtual SimpleHolder* clone() const;
    
    ~LESModelHolder();
    
    void operator()( const LESModelHolder& );
    
    using  boost::shared_ptr< LESModel >::operator*;
    using  boost::shared_ptr< LESModel >::operator->;

  };

} //incompressible
} // Foam


//---------------------------------------------------------------------------
#endif
