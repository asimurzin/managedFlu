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
      Deps( const std::set< holderPtr >& the_deps );
      Deps( const Deps&, const Deps& );
      Deps( const Deps&, const Deps&, const Deps& );
      Deps( const Deps&, const Deps&, const Deps&, const Deps& );
      
      
    private:
      Deps(); //not implemented
      //Deps( const Deps&); //not implemented
      //void operator=( const Deps&); //not implemented

  };

   
} // Foam


//---------------------------------------------------------------------------
#endif

