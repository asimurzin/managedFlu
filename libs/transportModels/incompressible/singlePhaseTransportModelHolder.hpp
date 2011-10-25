#ifndef singlePhaseTransportModelHolder_hpp
#define singlePhaseTransportModelHolder_hpp


//---------------------------------------------------------------------------
#include "transportModelHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <singlePhaseTransportModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class singlePhaseTransportModelHolder 
    : public transportModelHolder
    , public boost::shared_ptr< singlePhaseTransportModel >
  {
  public:
    singlePhaseTransportModelHolder( const volVectorFieldHolder&, const surfaceScalarFieldHolder& );
    singlePhaseTransportModelHolder();
    
    ~singlePhaseTransportModelHolder();
    
    virtual SimpleHolder* clone() const;
    
    void operator()( const singlePhaseTransportModelHolder& );
    
    using  boost::shared_ptr< singlePhaseTransportModel >::operator*;
    using  boost::shared_ptr< singlePhaseTransportModel >::operator->;
  protected:
    void operator=( const boost::shared_ptr< singlePhaseTransportModel >& );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
