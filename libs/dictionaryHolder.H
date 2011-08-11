#ifndef dictionaryHolder_H
#define dictionaryHolder_H


//---------------------------------------------------------------------------
#include <dictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class dictionaryHolder 
    : public boost::shared_ptr< dictionary >
  {
  protected:
    dictionaryHolder( const boost::shared_ptr< dictionary >& );
    dictionaryHolder();

  };
} // Foam


//---------------------------------------------------------------------------
#endif
