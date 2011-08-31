#ifndef Deps_hpp
#define Deps_hpp


//---------------------------------------------------------------------------
#include "SimpleHolder.hpp"
#include "Args.hpp"


namespace Foam
{
  
  class Deps 
    : public Args
  {
    public:
      Deps( const SimpleHolder* );
      Deps( const std::set< holderPtr >& );
      
    private:
      Deps(); //not implemented
      //Deps( const Deps&); //not implemented
      void operator=( const Deps&); //not implemented

  };

 Deps deps( const Deps& deps1 );
 Deps deps( const Deps& deps1, const Deps& deps2 );
    
} // Foam


//---------------------------------------------------------------------------
#endif

