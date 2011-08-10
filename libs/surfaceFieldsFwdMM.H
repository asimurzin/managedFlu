#ifndef surfaceFieldsFwdMM_H
#define surfaceFieldsFwdMM_H


//---------------------------------------------------------------------------
#include <surfaceFieldsFwd.H>


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type, template<class> class PatchField, class GeoMesh>
  class GeometricFieldHolder;

  typedef GeometricFieldHolder<scalar, fvsPatchField, surfaceMesh> surfaceScalarFieldHolder;
  typedef GeometricFieldHolder<vector, fvsPatchField, surfaceMesh> surfaceVectorFieldHolder;
  
} // Foam


//---------------------------------------------------------------------------
#endif
