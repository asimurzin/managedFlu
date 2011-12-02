#ifndef LESModelHolder_010701_free_hpp
#define LESModelHolder_010701_free_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "turbulenceModelHolder.hpp"
#include "transportModelHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


#include <LESModel.H>
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

    LESModelHolder();
    
    static LESModelHolder New( 
      const volVectorFieldHolder& U,
      const surfaceScalarFieldHolder& phi,
      transportModelHolder& transport );

    virtual SimpleHolder* clone() const;
    
    ~LESModelHolder();
    
    using  boost::shared_ptr< LESModel >::operator*;
    using  boost::shared_ptr< LESModel >::operator->;
  protected:
    LESModelHolder( 
      const boost::shared_ptr< LESModel >&, 
      const volVectorFieldHolder&,
      const surfaceScalarFieldHolder&,
      transportModelHolder& );

  };

} //incompressible
} // Foam


//---------------------------------------------------------------------------
#endif
