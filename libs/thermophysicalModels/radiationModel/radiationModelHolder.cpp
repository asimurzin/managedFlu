//---------------------------------------------------------------------------
#include "radiationModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace radiation
  {

    radiationModelHolder::radiationModelHolder( const boost::shared_ptr< radiationModel >& bt, const volScalarFieldHolder& T ) 
      : DependentHolder( Foam::deps( &T ) )
      , boost::shared_ptr< radiationModel >( bt )
    {}

    radiationModelHolder::radiationModelHolder() 
      : DependentHolder()
      , boost::shared_ptr< radiationModel >()
    {}

    radiationModelHolder radiationModelHolder::New( const volScalarFieldHolder& T )
    {
      autoPtr< radiationModel > a_model = radiationModel::New( T() ) ;
      
      return radiationModelHolder( boost::shared_ptr< radiationModel >( a_model.ptr() ), T );
    }
    
    universalHolder* radiationModelHolder::clone() const
    {
      return new radiationModelHolder( *this );
    }
    
    radiationModelHolder::~radiationModelHolder()
    {
#ifdef OUR_DEBUG
      cout << "~radiationModelHolder = " << this << nl;
#endif
    }
  }
}


//---------------------------------------------------------------------------
