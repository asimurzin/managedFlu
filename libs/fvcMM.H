#ifndef fvcMM_H
#define fvcMM_H


//---------------------------------------------------------------------------
#include <fvc.H>
#include "surfaceScalarFieldHolder.H"
#include "volScalarFieldHolder.H"
#include "volVectorFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
  
  
  //---------------------------------------------------------------------------
  //fvc::surfaceSum
    inline volScalarFieldHolder surfaceSum( const surfaceScalarFieldHolder& field )
    {
     return volScalarFieldHolder( surfaceSum( field() ), field.get_fvMeshArg() );
    }


  //---------------------------------------------------------------------------
  // fvc::grad    
    inline volVectorFieldHolder grad( const surfaceScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), field.get_fvMeshArg() );
    }

    inline volVectorFieldHolder grad( const volScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), field.get_fvMeshArg() );
    }

  }
} //Foam


//---------------------------------------------------------------------------
#endif
