#ifndef fvScalarMatrixArgs_H
#define fvScalarMatrixArgs_H


//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <volFields.H>

//---------------------------------------------------------------------------
namespace Foam
{
  class fvMeshHolder;
  class volScalarFieldHolder;
   
  class fvScalarMatrixArgs
  {
  public:
    const fvMeshHolder& get_fvMeshArg() const;
    const volScalarFieldHolder& get_fieldArg() const;
  protected:
    fvScalarMatrixArgs( const volScalarFieldHolder&, const fvMeshHolder&);
  private:
    boost::shared_ptr< volScalarFieldHolder > fieldArg;
    boost::shared_ptr< fvMeshHolder > fvMeshArg;
    //fvScalarMatrixArgs( const fvScalarMatrixArgs& ); // not implemented 
    void operator = ( const fvScalarMatrixArgs& ); // not implemented 
    fvScalarMatrixArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
