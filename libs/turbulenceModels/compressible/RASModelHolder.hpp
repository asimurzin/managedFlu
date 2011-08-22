#ifndef compressibleRASModelHolder_hpp
#define compressibleRASModelHolder_hpp


//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp" 

#include <compressible/RAS/RASModel/RASModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class RASModelHolder 
    : protected turbulenceModelArgs
    , public boost::shared_ptr< RASModel >
  {
  public:
    RASModelHolder( 
      const boost::shared_ptr< RASModel >&, 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder& );

    static RASModelHolder New( 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder& );
    
    ~RASModelHolder();
    
    using  boost::shared_ptr< RASModel >::operator*;
    using  boost::shared_ptr< RASModel >::operator->;

  private:
    RASModelHolder(); // not implemented
    //RASModelHolder( const RASModelHolder& ); // not implemented
    void operator=( const RASModelHolder& ); // not implemented

  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
