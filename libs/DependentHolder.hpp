#ifndef DependentHolder_hpp
#define DependentHolder_hpp


//---------------------------------------------------------------------------
#include "Args.hpp"
#include "SimpleHolder.hpp"
#include "Deps.hpp"

namespace Foam
{
  class DependentHolder
    : public Args
    , virtual public SimpleHolder
  {
    public:
      
      DependentHolder( const Deps& dp );
      
      const Deps deps() const;
      
      DependentHolder();
      
      virtual ~DependentHolder();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
