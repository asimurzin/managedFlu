#ifndef fvMatrixHolder_hpp
#define fvMatrixHolder_hpp


//---------------------------------------------------------------------------
#include "universalHolder.hpp"
#include "fvMatrixArgs.hpp"
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "smart_tmp/smart_tmp.hpp"

#include <fvMatrices.H>


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  class fvMatrixHolder 
    : public fvMatrixArgs< Type >
    , public smart_tmp< fvMatrix< Type > >
    , public universalHolder
  {
  public:
    fvMatrixHolder( const tmp< fvMatrix< Type > >& , const GeometricFieldHolder< Type, fvPatchField, volMesh >& );
    
    fvMatrixHolder( const fvMatrix< Type >& , const universalArgs& );
    fvMatrixHolder( const tmp< fvMatrix< Type > >& , const universalArgs& );
    
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
