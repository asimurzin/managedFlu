//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
//  Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
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
#ifndef turbulenceModelHolder_020000_hpp
#define turbulenceModelHolder_020000_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "volFields.hpp"
#include "basicThermoHolder.hpp"


#include <compressible/turbulenceModel/turbulenceModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class turbulenceModelHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< turbulenceModel >
  {
  public:
    turbulenceModelHolder();
    
    ~turbulenceModelHolder();
    
    static turbulenceModelHolder New( const volScalarFieldHolder& rho,
                                      const volVectorFieldHolder& U,
                                      const surfaceScalarFieldHolder& phi,
                                      const basicThermoHolder& thermoPhysicalModel,
                                      const word& turbulenceModelName = turbulenceModel::typeName );
    
    virtual SimpleHolder* clone() const;
    
    void operator()( const turbulenceModelHolder& );
    
    using  boost::shared_ptr< turbulenceModel >::operator*;
    using  boost::shared_ptr< turbulenceModel >::operator->;

  protected:
    turbulenceModelHolder( const boost::shared_ptr< turbulenceModel >& tm, 
                           const volScalarFieldHolder& rho,
                           const volVectorFieldHolder& U,
                           const surfaceScalarFieldHolder& phi, 
                           const basicThermoHolder& thermoPhysicalModel );
    void operator=( const boost::shared_ptr< turbulenceModel >& );
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
