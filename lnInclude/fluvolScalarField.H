#ifndef fluvolScalarField_H
#define fluvolScalarField_H


//---------------------------------------------------------------------------
#include <volFields.H>
#include "fvMeshHolder.H"

namespace Foam
{
  class fluvolScalarField : 
    protected fvMeshHolder
    , public volScalarField
  {
  private:
    fluvolScalarField( const IOobjectHolder& io, const fvMeshHolder& mesh );
    fluvolScalarField( const fluvolScalarField& ); // not implemented
    fluvolScalarField(); // not implemented
    friend class volScalarFieldHolder;
  public:
    ~fluvolScalarField();
  };
} // Foam

#endif
