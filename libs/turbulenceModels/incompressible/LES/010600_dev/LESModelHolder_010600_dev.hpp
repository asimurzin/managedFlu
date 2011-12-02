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
#ifndef LESModelHolder_010600_dev_hpp
#define LESModelHolder_010600_dev_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "turbulenceModelHolder.hpp"
#include "transportModelHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"


#include <incompressible/LES/LESModel/LESModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace incompressible
{
  class LESModelHolder 
    : public turbulenceModelHolder
    , public boost::shared_ptr< LESModel >
  {
  public:

    LESModelHolder();
    
    static LESModelHolder New( 
      const volVectorFieldHolder& U,
      const surfaceScalarFieldHolder& phi,
      transportModelHolder& transport );

    virtual SimpleHolder* clone() const;
    
    ~LESModelHolder();
    
    using  boost::shared_ptr< LESModel >::operator*;
    using  boost::shared_ptr< LESModel >::operator->;
  protected:
    LESModelHolder( 
      const boost::shared_ptr< LESModel >&, 
      const volVectorFieldHolder&,
      const surfaceScalarFieldHolder&,
      transportModelHolder& );

  };

} //incompressible
} // Foam


//---------------------------------------------------------------------------
#endif
