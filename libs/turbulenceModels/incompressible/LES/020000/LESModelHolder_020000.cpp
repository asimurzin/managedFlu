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
    transportModelHolder& transport,
    const word& turbulenceModelName )
  {
    autoPtr< LESModel > result = LESModel::New( U(), phi(), *transport, turbulenceModelName );
    
    return LESModelHolder( boost::shared_ptr< LESModel >( result.ptr() ), U, phi, transport );
  }

  SimpleHolder* LESModelHolder::clone() const
  {
    return new LESModelHolder( *this );
  }

  LESModelHolder::~LESModelHolder()
  {}
  
  void LESModelHolder::operator()( const LESModelHolder& model )
  {
    this->operator=( model );
  }
  
}//incompressible
}//Foam

//---------------------------------------------------------------------------
