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
#ifndef singlePhaseTransportModelHolder_hpp
#define singlePhaseTransportModelHolder_hpp


//---------------------------------------------------------------------------
#include "transportModelHolder.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"

#include <singlePhaseTransportModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class singlePhaseTransportModelHolder 
    : public transportModelHolder
    , public boost::shared_ptr< singlePhaseTransportModel >
  {
  public:
    singlePhaseTransportModelHolder( const volVectorFieldHolder&, const surfaceScalarFieldHolder& );
    singlePhaseTransportModelHolder();
    
    ~singlePhaseTransportModelHolder();
    
    virtual SimpleHolder* clone() const;
    
    void operator()( const singlePhaseTransportModelHolder& );
    
    using  boost::shared_ptr< singlePhaseTransportModel >::operator*;
    using  boost::shared_ptr< singlePhaseTransportModel >::operator->;
  protected:
    void operator=( const boost::shared_ptr< singlePhaseTransportModel >& );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
