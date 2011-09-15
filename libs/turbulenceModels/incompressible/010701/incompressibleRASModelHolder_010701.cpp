//---------------------------------------------------------------------------
#include "incompressibleRASModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace incompressible
{
  RASModelHolder::RASModelHolder( 
    const boost::shared_ptr< RASModel >& tm, 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
    : DependentHolder( Deps( &U, &phi, &transport ) )
    , boost::shared_ptr< RASModel >( tm )
  {
    turbulenceModelHolder::operator=( boost::shared_ptr< RASModel >( *this ) );
  }

  RASModelHolder::RASModelHolder()
    : DependentHolder()
    , boost::shared_ptr< RASModel >()
  {}

  RASModelHolder RASModelHolder::New( 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
  {
    autoPtr< RASModel > result = RASModel::New( U(), phi(), *transport );
    
    return RASModelHolder( boost::shared_ptr< RASModel >( result.ptr() ), U, phi, transport );
  }

  SimpleHolder* RASModelHolder::clone() const
  {
    return new RASModelHolder( *this );
  }

  RASModelHolder::~RASModelHolder()
  {}
  
}//incompressible
}//Foam

//---------------------------------------------------------------------------
