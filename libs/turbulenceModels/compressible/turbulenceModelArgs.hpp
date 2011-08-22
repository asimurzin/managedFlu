#ifndef turbulenceModelArgs_hpp
#define turbulenceModelArgs_hpp


//---------------------------------------------------------------------------
#include "volFields.hpp"
#include "surfaceFields.hpp"
#include "basicThermoHolder.hpp"


#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class turbulenceModelArgs
  {
  public:
    const volScalarFieldHolder& rho() const ;
    const volVectorFieldHolder& U() const ;
    const surfaceScalarFieldHolder& phi() const ;
    const basicThermoHolder& thermo() const ;

  protected:
    turbulenceModelArgs( 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarField&, 
      const basicThermoHolder& );
    
  private:
    boost::shared_ptr< volScalarFieldHolder > rho_;
    boost::shared_ptr< volVectorFieldHolder > U_;
    boost::shared_ptr< surfaceScalarFieldHolder >  phi_;
    boost::shared_ptr< basicThermoHolder > thermophysicalModel_;
    
    turbulenceModelArgs(); // not implemented
    //turbulenceModelArgs( const turbulenceModelArgs& ); // not implemented 
    void operator=( const turbulenceModelArgs& ); // not implemented 
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
