#ifndef fvMatrixArgs_H
#define fvMatrixArgs_H


//---------------------------------------------------------------------------
#include "volFields.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
  
  template<class Type> 
  class fvMatrixArgs
  {
  public:
    GeometricFieldHolder< Type, fvPatchField, volMesh >& psi() const;
    fvMatrixArgs();
    
  protected:
    fvMatrixArgs( const GeometricFieldHolder< Type, fvPatchField, volMesh >& );

  private:
    boost::shared_ptr< GeometricFieldHolder< Type, fvPatchField, volMesh > > psi_;

    // fvMatrixArgs( const fvMatrixArgs& ); // not implemented 
    //void operator = ( const fvMatrixArgs< Type >& ); // not implemented 
    //fvMatrixArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#include "fvMatrixArgs.C"


//---------------------------------------------------------------------------
#endif
