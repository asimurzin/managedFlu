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


  //---------------------------------------------------------------------------
  // fvc::ddtPhiCorr    
    inline surfaceScalarFieldHolder ddtPhiCorr( const volScalarFieldHolder& rA,
                                                const volVectorFieldHolder& U,
                                                const surfaceScalarFieldHolder& phi )
    {
      return surfaceScalarFieldHolder( ddtPhiCorr( rA(), U(), phi() ), rA.get_fvMeshArg() );
    }                   

  //---------------------------------------------------------------------------
  // fvc::div    
    inline volScalarFieldHolder div( const surfaceScalarFieldHolder& phi )
    {
      return volScalarFieldHolder( div( phi() ), phi.get_fvMeshArg() );
    }                   


  }
} //Foam


//---------------------------------------------------------------------------
#endif
