#ifndef fvMatrixHolder_hpp
#define fvMatrixHolder_hpp


//---------------------------------------------------------------------------
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
  {
  public:
    fvMatrixHolder( const tmp< fvMatrix< Type > >& , const GeometricFieldHolder< Type, fvPatchField, volMesh >& );
    fvMatrixHolder();
    ~fvMatrixHolder();
    
    void operator = ( const fvMatrixHolder& );

    // re-define functions which returns "holders"
    volScalarFieldHolder A() const
    {
      return  volScalarFieldHolder( this->operator()().A(), this->psi().mesh() );
    }
    GeometricFieldHolder< Type, fvPatchField, volMesh > H() const
    {
      return  GeometricFieldHolder< Type, fvPatchField, volMesh >( this->operator()().H(), this->psi().mesh() );
    }
    
    volScalarFieldHolder H1() const
    {
      return  volScalarFieldHolder( this->operator()().H1(), this->psi().mesh() );
    }
    GeometricFieldHolder< Type, fvsPatchField, surfaceMesh > flux() const
    {
      return  GeometricFieldHolder< Type, fvsPatchField, surfaceMesh >( this->operator()().flux(), this->psi().mesh() );
    }
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
