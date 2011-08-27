#ifndef radiationModelHolder_hpp
#define radiationModelHolder_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "universalHolder.hpp"
#include "radiationModelArgs.hpp"
#include "volFields.hpp"

#include <radiationModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  namespace radiation
  {
    class radiationModelHolder 
      : protected radiationModelArgs
      , public boost::shared_ptr< radiationModel >
      , public universalHolder
    {
    public:
      radiationModelHolder( const boost::shared_ptr< radiationModel >&, const volScalarFieldHolder& );
      radiationModelHolder();
    
      ~radiationModelHolder();
    
      static radiationModelHolder New( const volScalarFieldHolder& T );
    
      virtual universalHolder* clone() const;
    
      using  boost::shared_ptr< radiationModel >::operator*;
      using  boost::shared_ptr< radiationModel >::operator->;

    };
  }
} // Foam


//---------------------------------------------------------------------------
#endif
