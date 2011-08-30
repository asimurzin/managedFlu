#ifndef fvm_hpp
#define fvm_hpp


//---------------------------------------------------------------------------
#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "fvMatrices.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder ddt( const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), deps( &field ) );
    }


    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, 
				     const volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( div( field1(), field2() ), deps( &field1, &field2 ) );
    }
    

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder laplacian( const dimensionedScalar& ds, 
                                           const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( laplacian( ds, field() ), deps( &field ) );
    }

    inline fvScalarMatrixHolder laplacian( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
    {
      return fvScalarMatrixHolder( laplacian( field1(), field2() ), deps( &field1, &field2 )  );
    }
  } // fvm
} // Foam


//---------------------------------------------------------------------------
#endif
