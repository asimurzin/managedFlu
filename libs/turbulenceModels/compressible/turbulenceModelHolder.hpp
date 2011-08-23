#ifndef compressibleturbulenceModelHolder_hpp
#define compressibleturbulenceModelHolder_hpp


//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp" 

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
  {
  public:
    turbulenceModelHolder( 
      const boost::shared_ptr< turbulenceModel >&, 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder& );

    ~turbulenceModelHolder();
    
    using  boost::shared_ptr< turbulenceModel >::operator*;
    using  boost::shared_ptr< turbulenceModel >::operator->;

  private:
    turbulenceModelHolder(); // not implemented
    //turbulenceModelHolder( const turbulenceModelHolder& ); // not implemented
    void operator=( const turbulenceModelHolder& ); // not implemented

  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
