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

    smart_tmp<T>()
      : px( 0 ), pn()
    {}
    
    template< class Y >
    explicit smart_tmp( Y* p = 0 )
      : px( p ) 
      , pn( new tmp< T >( p ) )
    {}
    
    smart_tmp( const T& tRef )
      : px( const_cast< T* >( &tRef ) )
      , pn( new tmp< T >( tRef ) )
    {}
    
    smart_tmp( const tmp< T >& t )
      : px( const_cast< T* >( t.operator->() ) )
      , pn( new tmp< T >( t ) )
    {}
    
    template< class Y >
    smart_tmp( const smart_tmp< Y >& at )
      : px( at.px )
      , pn( at.pn )
    {}
    
    smart_tmp& operator=( const tmp< T >& t )
    {
      smart_tmp< T >( t ).swap(*this);
      return *this;
    }
    
    template< class Y >
    smart_tmp& operator=( const smart_tmp< Y >& at )
    {
      smart_tmp< T >( at ).swap(*this);
      return *this;
    }
    
    T* operator->()
    {
      BOOST_ASSERT(px != 0);
      return px;
    }
    
    const T* operator->() const
    {
      BOOST_ASSERT(px != 0);
      return px;
    }
    
    T& operator()()
    {
      BOOST_ASSERT(px != 0);
      return *px;
    }
    
    const T& operator()() const
    {
      BOOST_ASSERT(px != 0);
      return *px;
    }
    
    bool empty() const
    {
      return px == 0;
    }
    
    void swap( smart_tmp< T > & other )
    {
      std::swap(px, other.px);
      pn.swap(other.pn);
    }
  
    private:
      template<class Y> friend class smart_tmp;
      T * px;                     // contained pointer
      boost::detail::shared_count pn;    // reference counter
  };
  
  
  //---------------------------------------------------------------------------
}


//---------------------------------------------------------------------------
#endif

