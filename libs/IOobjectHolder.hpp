#ifndef IOobjectHolder_hpp
#define IOobjectHolder_hpp


//---------------------------------------------------------------------------
#include "Args.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"

#include <IOobject.H>
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
   
  class IOobjectHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< IOobject >
  {
  public:
    IOobjectHolder( const word &name, 
                    const fileName &instance, 
                    const objectRegistryHolder & registry, 
                    IOobject::readOption r = IOobject::NO_READ, 
                    IOobject::writeOption w = IOobject::NO_WRITE, 
                    bool registerObject=true );
    
    virtual SimpleHolder* clone() const;
    
    ~IOobjectHolder();

    using  boost::shared_ptr< IOobject >::operator*;
    using  boost::shared_ptr< IOobject >::operator->;

  protected:
    void operator=( const boost::shared_ptr< IOobject >& ); 
    IOobjectHolder();

  };
} // Foam


//---------------------------------------------------------------------------
#endif
