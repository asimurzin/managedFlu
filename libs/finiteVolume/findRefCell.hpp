#ifndef findRefCell_hpp
#define findRefCell_hpp


//---------------------------------------------------------------------------
#include <findRefCell.H>
#include "volFields.hpp"
#include "surfaceFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  inline void setRefCell( const volScalarFieldHolder& field,
    const volScalarFieldHolder& fieldRef,
    const dictionary& dict,
    label& refCelli,
    scalar& refValue,
    const bool forceReference = false )
  {
   setRefCell( field(), fieldRef(), dict, refCelli, refValue, forceReference );
  }
  
  inline void setRefCell( const volScalarFieldHolder& field,
    const dictionary& dict,
    label& refCelli,
    scalar& refValue,
    const bool forceReference = false )
  {
    setRefCell( field(), dict, refCelli, refValue, forceReference );
  }
  
  scalar getRefCellValue( const volScalarFieldHolder& field, const label refCelli )
  {
    return getRefCellValue( field(), refCelli );
  }

} // Foam


//---------------------------------------------------------------------------
#endif
