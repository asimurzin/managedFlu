//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  See http://sourceforge.net/projects/pythonflu
//
//  Author : Alexey PETROV, Andrey Simurzin


//---------------------------------------------------------------------------
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
