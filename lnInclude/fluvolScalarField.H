#ifndef fluvolScalarField_H
#define fluvolScalarField_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include "fvMeshHolder.H"

namespace Foam
{
  class fluvolScalarField : public fvMeshHolder, public volScalarField
  {
  private:
    fluvolScalarField( const IOobject& io, const fvMeshHolder& mesh ) : fvMeshHolder( mesh ),
                                                                        volScalarField( io, *mesh )
    {
      cout << "fluvolScalarField = " << this << nl;
    }
    fluvolScalarField( const fluvolScalarField& ); // not implemented
    fluvolScalarField(); // not implemented
    friend class volScalarFieldHolder;
  public:
    ~fluvolScalarField()
    {
      cout << "~fluvolScalarField = " << this << nl;
    }
  };
} // Foam

#endif
