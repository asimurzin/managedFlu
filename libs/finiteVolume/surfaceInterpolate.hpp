#ifndef surfaceInterpolate_hpp
#define surfaceInterpolate_hpp


//---------------------------------------------------------------------------
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <surfaceInterpolate.H>


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    template<class Type>
    inline GeometricFieldHolder< Type, fvsPatchField, surfaceMesh > interpolate( const GeometricFieldHolder<Type, fvPatchField, volMesh>& field )
    {
      return GeometricFieldHolder< Type, fvsPatchField, surfaceMesh >( interpolate( field() ), &field );
    }
  }
} // Foam


//---------------------------------------------------------------------------
#endif
