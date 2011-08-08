#ifndef fvmMM_H
#define fvmMM_H


//---------------------------------------------------------------------------
#include <fvm.H>
#include <dimensionedScalar.H>
#include "volVectorFieldHolder.H"
#include "fvVectorMatrixHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    inline fvVectorMatrixHolder ddt( const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), field);
    }

    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, const volVectorFieldHolder& field2 )
    {
        return fvVectorMatrixHolder( div( field1(), field2() ), field2 );
    }

    inline fvVectorMatrixHolder laplacian( const dimensionedScalar& ds, const volVectorFieldHolder& field2 )
    {
        return fvVectorMatrixHolder( laplacian( ds, field2() ), field2 );
    }
  }
} // Foam


//---------------------------------------------------------------------------
#endif
