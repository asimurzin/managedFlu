#ifndef dictionaryHolder_H
#define dictionaryHolder_H


//---------------------------------------------------------------------------
#include <dictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class dictionaryHolder : 
      public boost::shared_ptr< dictionary >
//    , protected dictionaryNameHolder
      
  {
  protected:
    dictionaryHolder( const boost::shared_ptr<Foam::dictionary>& );
    dictionaryHolder();
  private:
//    dictionaryHolder( const dictionaryHolder& ); // not implemented 
    void operator = ( const dictionaryHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
