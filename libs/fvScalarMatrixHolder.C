//---------------------------------------------------------------------------
#include "fvScalarMatrixHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  fvScalarMatrixHolder::fvScalarMatrixHolder( const tmp< fvScalarMatrix>& tmp_mt, 
					      const volScalarFieldHolder& field ) 
    : fvScalarMatrixArgs( field, field.mesh() )
    , tmp< fvScalarMatrix >( tmp_mt )
  {
#ifdef OUR_DEBUG
    cout << "flufvScalarMatrix = " << this << nl;
#endif
  }
  
  fvScalarMatrixHolder::~fvScalarMatrixHolder()
  {
#ifdef OUR_DEBUG
    cout << "~flufvScalarMatrix = " << this << nl;
#endif
  }
} //Foam


//---------------------------------------------------------------------------
