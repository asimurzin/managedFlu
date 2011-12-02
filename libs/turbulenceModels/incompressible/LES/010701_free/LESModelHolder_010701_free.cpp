//---------------------------------------------------------------------------
#include "LESModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace incompressible
{
  LESModelHolder::LESModelHolder( 
    const boost::shared_ptr< LESModel >& tm, 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
    : DependentHolder( Deps( &U, &phi, &transport ) )
    , boost::shared_ptr< LESModel >( tm )
  {
    turbulenceModelHolder::operator=( boost::shared_ptr< LESModel >( *this ) );
  }

  LESModelHolder::LESModelHolder()
    : DependentHolder()
    , boost::shared_ptr< LESModel >()
  {}

  LESModelHolder LESModelHolder::New( 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
  {
    autoPtr< LESModel > result = LESModel::New( U(), phi(), *transport );
    
    return LESModelHolder( boost::shared_ptr< LESModel >( result.ptr() ), U, phi, transport );
  }

  SimpleHolder* LESModelHolder::clone() const
  {
    return new LESModelHolder( *this );
  }

  LESModelHolder::~LESModelHolder()
  {}
  
}//incompressible
}//Foam

//---------------------------------------------------------------------------