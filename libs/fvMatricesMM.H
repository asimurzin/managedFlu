#ifndef fvMatricesMM_H
#define fvMatricesMM_H


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
