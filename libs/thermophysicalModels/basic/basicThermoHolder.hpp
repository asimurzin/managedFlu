#ifndef basicThermoHolder_hpp
#define basicThermoHolder_hpp


//---------------------------------------------------------------------------
#include "basicThermoArgs.hpp" 

#include <basicThermo.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class basicThermoHolder 
    : protected basicThermoArgs
    , public boost::shared_ptr< basicThermo >
  {
  public:
    basicThermoHolder( const boost::shared_ptr< basicThermo >&, const fvMeshHolder& );
    ~basicThermoHolder();
    
    using  boost::shared_ptr< basicThermo >::operator*;
    using  boost::shared_ptr< basicThermo >::operator->;

  private:
    basicThermoHolder(); // not implemented
    //basicThermoHolder( const basicThermoHolder& ); // not implemented
    void operator=( const basicThermoHolder& ); // not implemented

  };
} // Foam


//---------------------------------------------------------------------------
#endif
