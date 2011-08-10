#ifndef fvcMM_H
#define fvcMM_H


//---------------------------------------------------------------------------
#include <fvc.H>
#include "surfaceFieldsMM.H"
#include "volFieldsMM.H"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
  
  
  //---------------------------------------------------------------------------
  //fvc::surfaceSum
    inline volScalarFieldHolder surfaceSum( const surfaceScalarFieldHolder& field )
    {
     return volScalarFieldHolder( surfaceSum( field() ), field.mesh() );
    }


  //---------------------------------------------------------------------------
  // fvc::grad    
    inline volVectorFieldHolder grad( const surfaceScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), field.mesh() );
    }

    inline volVectorFieldHolder grad( const volScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), field.mesh() );
    }


  //---------------------------------------------------------------------------
  // fvc::ddtPhiCorr    
    inline surfaceScalarFieldHolder ddtPhiCorr( const volScalarFieldHolder& rA,
                                                const volVectorFieldHolder& U,
                                                const surfaceScalarFieldHolder& phi )
    {
      return surfaceScalarFieldHolder( ddtPhiCorr( rA(), U(), phi() ), rA.mesh() );
    }                   

  //---------------------------------------------------------------------------
  // fvc::div    
    inline volScalarFieldHolder div( const surfaceScalarFieldHolder& phi )
    {
      return volScalarFieldHolder( div( phi() ), phi.mesh() );
    }                   


  }
} //Foam


//---------------------------------------------------------------------------
#endif
