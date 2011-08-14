#ifndef volFields_hpp
#define volFields_hpp


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
