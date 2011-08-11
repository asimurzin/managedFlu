#ifndef fvVectorMatrixArgs_H
#define fvVectorMatrixArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "volFieldsMM.H"

//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
   
  class fvVectorMatrixArgs
  {
  public:
    const fvMeshHolder& get_fvMeshArg() const;
    const volVectorFieldHolder& get_fieldArg() const;

  protected:
    fvVectorMatrixArgs( const volVectorFieldHolder&, const fvMeshHolder&);

  private:
    boost::shared_ptr< volVectorFieldHolder > fieldArg;
    boost::shared_ptr< fvMeshHolder > fvMeshArg;

  private:
    // fvVectorMatrixArgs( const fvVectorMatrixArgs& ); // not implemented 
    void operator = ( const fvVectorMatrixArgs& ); // not implemented 
    fvVectorMatrixArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
