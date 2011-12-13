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
#ifndef fvMatrixHolder_hpp
#define fvMatrixHolder_hpp


//---------------------------------------------------------------------------
#include "SimpleHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "smart_tmp/smart_tmp.hpp"

#include <fvMatrices.H>


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  class fvMatrixHolder 
    : virtual public DependentHolder
    , public smart_tmp< fvMatrix< Type > >
  {
  public:
    fvMatrixHolder( const smart_tmp< fvMatrix< Type > >& , const Deps& );
    
    fvMatrixHolder();
    
    virtual SimpleHolder* clone() const;
    
    ~fvMatrixHolder();
    
    void operator = ( const fvMatrixHolder< Type >& );
    
    void operator()( const fvMatrixHolder< Type >& );
#ifndef SWIG
    using Foam::smart_tmp< fvMatrix< Type > >::operator();
#endif
};

  template< class Type >
  lduMatrix::solverPerformance solve( fvMatrixHolder< Type > mt , const dictionary& dict )
  {
    return solve( mt(), dict );
  }


  template<class Type>
  lduMatrix::solverPerformance solve( fvMatrixHolder< Type > mt )
  {
    return solve( mt() );  
  }
 
} // Foam


//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const smart_tmp< fvMatrix< Type > >& mt, 
					  const Deps& args ) 
    : DependentHolder( args )
    , smart_tmp< fvMatrix< Type > >( mt )
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }


template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder() 
    : DependentHolder()
    , smart_tmp< fvMatrix< Type > >()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  SimpleHolder* fvMatrixHolder< Type >::clone() const
  {
    return new fvMatrixHolder< Type >( *this );
  }
  
  template<class Type>
  fvMatrixHolder< Type >::~fvMatrixHolder()
  {
#ifdef OUR_DEBUG
    cout << "~flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  void fvMatrixHolder< Type >::operator = ( const fvMatrixHolder< Type >& mt)
  {
    if ( this->empty() )
    {
      Args::operator=( mt );
      smart_tmp< fvMatrix< Type > >::operator=( mt );
    }
    else
    {
      this->operator()() = mt();
    }
  }
  
  template<class Type>
  void fvMatrixHolder< Type >::operator () ( const fvMatrixHolder< Type >& mt)
  {
      Args::operator=( mt );
      smart_tmp< fvMatrix< Type > >::operator=( mt );
  }
} //Foam



//---------------------------------------------------------------------------
#endif
