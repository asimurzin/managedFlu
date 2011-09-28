#ifndef volFieldsFwd_hpp
#define volFieldsFwd_hpp


//---------------------------------------------------------------------------
#include <volFieldsFwd.H>


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type, template<class> class PatchField, class GeoMesh>
  class GeometricFieldHolder;

  typedef GeometricFieldHolder<scalar, fvPatchField, volMesh> volScalarFieldHolder;
  typedef GeometricFieldHolder<vector, fvPatchField, volMesh> volVectorFieldHolder;
} // Foam


//---------------------------------------------------------------------------
#endif
