#ifndef fvMatrixHolder_hpp
#define fvMatrixHolder_hpp


//---------------------------------------------------------------------------
#include "universalHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "smart_tmp/smart_tmp.hpp"

#include <fvMatrices.H>


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  class fvMatrixHolder 
    : public DependentHolder
    , public smart_tmp< fvMatrix< Type > >
  {
  public:
    fvMatrixHolder( const fvMatrix< Type >& , const Deps& );
    fvMatrixHolder( const tmp< fvMatrix< Type > >& , const Deps& );
    
    fvMatrixHolder();
    
    virtual universalHolder* clone() const;
    
    ~fvMatrixHolder();
    
    void operator = ( const fvMatrixHolder& );

};

  template< class Type >
  lduMatrix::solverPerformance solve( fvMatrixHolder< Type > mt , const dictionary& dict )
  {
    return solve( mt(), dict );
  }


  template<class Type>
  lduMatrix::solverPerformance solve( fvMatrixHolder< Type > mt )
  {
    return solve( mt() );  
  }
 
} // Foam


//---------------------------------------------------------------------------
#include "fvMatrixHolder.cpp"


//---------------------------------------------------------------------------
#endif
