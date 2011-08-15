#ifndef fvMatrixHolder_H
#define fvMatrixHolder_H


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include <tmp.H>
#include "fvMatrixArgs.H"
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  class fvMatrixHolder 
    : public fvMatrixArgs< Type >
    , public tmp< fvMatrix< Type > >
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
    
  private:
    //fvMatrixHolder(); // not implemented
    // fvMatrixHolder( const fvMatrixHolder& ); // not implemented 
    //void operator = ( const fvMatrixHolder& ); // not implemented 
  };
  
} // Foam


//---------------------------------------------------------------------------
#include "fvMatrixHolder.C"


//---------------------------------------------------------------------------
#endif
