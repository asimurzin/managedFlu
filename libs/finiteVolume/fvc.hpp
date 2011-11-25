//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2011- Alexey Petrov
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
#ifndef fvc_hpp
#define fvc_hpp


//---------------------------------------------------------------------------
#include <fvc.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "GeometricFieldFunctions.hpp"

#include "fvcDDt.hpp"
#include "fvcGrad.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    //---------------------------------------------------------------------------
    inline volScalarFieldHolder surfaceSum( const surfaceScalarFieldHolder& field )
    {
      return volScalarFieldHolder( surfaceSum( field() ),  Deps( field.deps() ) );
    }


    //---------------------------------------------------------------------------
    inline surfaceScalarFieldHolder ddtPhiCorr( const volScalarFieldHolder& rA,
                                                const volVectorFieldHolder& U,
                                                const surfaceScalarFieldHolder& phi )
    {
      return surfaceScalarFieldHolder( ddtPhiCorr( rA(), U(), phi() ), Deps( rA.deps(), U.deps(), phi.deps() ) );
    }                   
    

    //---------------------------------------------------------------------------
    inline volScalarFieldHolder div( const surfaceScalarFieldHolder& phi )
    {
      return volScalarFieldHolder( div( phi() ), phi.deps() );
    }
    
    
    //---------------------------------------------------------------------------
    inline surfaceScalarFieldHolder snGrad( const volScalarFieldHolder& field)
    {
      return surfaceScalarFieldHolder( snGrad( field() ), field.deps() );
    }

    inline surfaceScalarFieldHolder snGrad( const volScalarFieldHolder& field, const word& name)
    {
      return surfaceScalarFieldHolder( snGrad( field(), name ), field.deps() );
    }

   //---------------------------------------------------------------------------
   inline volVectorFieldHolder reconstruct( const surfaceScalarFieldHolder& field )
   {
     return volVectorFieldHolder( reconstruct( field() ), field.deps() );
   }
   
   
   //---------------------------------------------------------------------------
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
