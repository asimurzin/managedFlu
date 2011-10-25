//---------------------------------------------------------------------------
#include "singlePhaseTransportModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  
  singlePhaseTransportModelHolder::singlePhaseTransportModelHolder( const volVectorFieldHolder& U, const surfaceScalarFieldHolder& phi )
    : DependentHolder( Deps( &U, &phi ) )
    , boost::shared_ptr< singlePhaseTransportModel >( new singlePhaseTransportModel( U(), phi() ) )
  {
    transportModelHolder::operator=( boost::shared_ptr< singlePhaseTransportModel >( *this ) );
  }
    
  singlePhaseTransportModelHolder::singlePhaseTransportModelHolder() 
    : transportModelHolder()
    , boost::shared_ptr< singlePhaseTransportModel >()
  {}

  void singlePhaseTransportModelHolder::operator=( const boost::shared_ptr< singlePhaseTransportModel >& bt ) 
  {
    boost::shared_ptr< singlePhaseTransportModel >::operator=( bt );
    transportModelHolder::operator=( bt );
  }

  SimpleHolder* singlePhaseTransportModelHolder::clone() const
  {
    return new singlePhaseTransportModelHolder( *this );
  }
  
  void singlePhaseTransportModelHolder::operator()( const singlePhaseTransportModelHolder& model )
  {
    this->operator=( model );
  }
  
  singlePhaseTransportModelHolder::~singlePhaseTransportModelHolder()
  {}
}


//---------------------------------------------------------------------------
