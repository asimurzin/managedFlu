#ifndef radiationModelHolder_hpp
#define radiationModelHolder_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "volFields.hpp"

#include <radiationModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  namespace radiation
  {
    class radiationModelHolder 
      : virtual public DependentHolder
      , public boost::shared_ptr< radiationModel >
    {
    public:
      radiationModelHolder();
    
      ~radiationModelHolder();
    
      static radiationModelHolder New( const volScalarFieldHolder& T );
    
      virtual SimpleHolder* clone() const;
      
      void operator()( const radiationModelHolder& );
    
      using  boost::shared_ptr< radiationModel >::operator*;
      using  boost::shared_ptr< radiationModel >::operator->;
    protected:
      radiationModelHolder( const boost::shared_ptr< radiationModel >&, const volScalarFieldHolder& );
    };
  }
} // Foam


//---------------------------------------------------------------------------
#endif
