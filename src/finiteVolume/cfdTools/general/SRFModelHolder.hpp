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
#ifndef SRFModelHolde_hpp
#define SRFModelHolder_hpp


//---------------------------------------------------------------------------
#include "volFields.hpp"
#include "IOdictionaryHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"

#include <SRFModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace SRF
{  
  class SRFModelHolder 
    : public IOdictionaryHolder
    , public boost::shared_ptr< SRFModel >
  {
  public:
    SRFModelHolder();

    static SRFModelHolder New( const volVectorFieldHolder& );
    
    ~SRFModelHolder();
    
    virtual SimpleHolder* clone() const;
    
    void operator()( const SRFModelHolder& );
    
    using  boost::shared_ptr< SRFModel >::operator*;
    using  boost::shared_ptr< SRFModel >::operator->;
  
  protected:
    void operator=( const boost::shared_ptr< SRFModel >& );
    SRFModelHolder( const boost::shared_ptr< SRFModel >&, const volVectorFieldHolder& );
  };
} // SRF
} // Foam


//---------------------------------------------------------------------------
#endif
