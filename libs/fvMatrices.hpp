#ifndef fvMatrices_hpp
#define fvMatrices_hpp


//---------------------------------------------------------------------------
#include <fvMatrices.H>
#include "fvMatrixHolder.H"



//---------------------------------------------------------------------------
namespace Foam
{
  typedef fvMatrixHolder<scalar> fvScalarMatrixHolder;
  typedef fvMatrixHolder<vector> fvVectorMatrixHolder;
}

//---------------------------------------------------------------------------
#endif
