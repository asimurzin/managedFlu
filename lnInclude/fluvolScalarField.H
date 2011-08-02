#ifndef fluvolScalarField_H
#define fluvolScalarField_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include "fvMeshHolder.H"

namespace Foam
{
  class fluvolScalarField : 
    public fvMeshHolder
    , public volScalarField
  {
  private:
    fluvolScalarField( const IOobjectHolder&, const fvMeshHolder& );
    fluvolScalarField( const fluvolScalarField& ); // not implemented
    fluvolScalarField(); // not implemented
    friend class volScalarFieldHolder;
  public:
    ~fluvolScalarField();
    fluvolScalarField( const tmp< volScalarField >&, const fvMeshHolder& );
  };
} // Foam

#endif
