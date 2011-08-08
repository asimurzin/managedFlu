//---------------------------------------------------------------------------
#include "fvVectorMatrixHolder.H"
#include "volVectorFieldHolder.H"

//---------------------------------------------------------------------------
namespace Foam
{

  fvVectorMatrixHolder::fvVectorMatrixHolder( const tmp< fvVectorMatrix>& tmp_mt, const volVectorFieldHolder& field ) : 
    fvVectorMatrixArgs( field, field.get_fvMeshArg() ), 
    tmp< fvVectorMatrix >( tmp_mt )
  {
#ifdef OUR_DEBUG
    cout << "flufvVectorMatrix = " << this << nl;
#endif
  }

  fvVectorMatrixHolder::~fvVectorMatrixHolder()
  {
#ifdef OUR_DEBUG
    cout << "~flufvVectorMatrix = " << this << nl;
#endif
  }

} //Foam


//---------------------------------------------------------------------------
