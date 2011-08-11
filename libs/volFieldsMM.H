#ifndef volFieldsMM_H
#define volFieldsMM_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include "GeometricFieldHolder.H"



//---------------------------------------------------------------------------
namespace Foam
{
  typedef GeometricFieldHolder< scalar, fvPatchField, volMesh > volScalarFieldHolder;
  typedef GeometricFieldHolder< vector, fvPatchField, volMesh > volVectorFieldHolder;
}

//---------------------------------------------------------------------------
#endif
