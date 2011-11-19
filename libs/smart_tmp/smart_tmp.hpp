//  pythonFlu - Python wrapping for OpenFOAM C++ API
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
//  Author : Alexey PETROV


//---------------------------------------------------------------------------
#ifndef smart_tmp_hpp
#define smart_tmp_hpp


//---------------------------------------------------------------------------
#include <tmp.H>

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  //---------------------------------------------------------------------------
  template< class T >
  struct smart_tmp
  {
    boost::shared_ptr< tmp< T > > engine;
    
    explicit smart_tmp( T* tPtr = 0 )
      : engine( boost::shared_ptr< tmp< T > >( new tmp< T >( tPtr ) ) )
    {}
    
    smart_tmp( const T& tRef )
      : engine( boost::shared_ptr< tmp< T > >( new tmp< T >( tRef ) ) )
    {}
    
    smart_tmp( const tmp< T >& t )
      : engine( boost::shared_ptr< tmp< T > >( new tmp< T >( t ) ) )
    {}
    
    smart_tmp( const smart_tmp< T >& at )
      : engine( at.engine )
    {}
    
    template< class Y >
    smart_tmp( const smart_tmp< Y >& at )
    {
      if ( ( *at.engine ).isTmp() )
      {
        this->engine = boost::shared_ptr< tmp< T > >( new tmp< T >( const_cast<Y*>( at.operator->() ) ) );
        this->operator->()->operator++();
      }
      else
      {
        this->engine = boost::shared_ptr< tmp< T > >( new tmp< T >( at() ) );
      }
    }
 
    void operator=( const tmp< T >& t )
    {
      this->engine = boost::shared_ptr< tmp< T > >( new tmp< T >( t ) );
    }
    
    void operator=( const smart_tmp< T >& at )
    {
      this->engine = at.engine;
    }
    
    template< class Y >
    void operator=( const smart_tmp< Y >& at )
    {
      if ( ( *at.engine ).isTmp() )
      {
        this->engine = boost::shared_ptr< tmp< T > >( new tmp< T >( const_cast<Y*>( at.operator->() ) ) );
        this->operator->()->operator++();
      }
      else
      {
        this->engine = boost::shared_ptr< tmp< T > >( new tmp< T >( at() ) );
      }
    }
    
    T* operator->()
    {
      return this->engine->operator -> ();
    }
    
    T* ptr()
    {
      T* ptr = this->engine->ptr();
      this->engine.reset();
      return ptr; 
    }
    
    const T* operator->() const
    {
      return this->engine->operator -> ();
    }
    
    T& operator()()
    {
      return this->engine->operator () ();
    }
    
    const T& operator()() const
    {
      return this->engine->operator () ();
    }
    
    bool empty() const
    {
      return this->engine->empty();
    }

  };
  
  
  //---------------------------------------------------------------------------
}


//---------------------------------------------------------------------------
#endif

