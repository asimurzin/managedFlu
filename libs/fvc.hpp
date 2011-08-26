#ifndef fvc_hpp
#define fvc_hpp


//---------------------------------------------------------------------------
#include <fvc.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "GeometricFieldFunctions.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    //---------------------------------------------------------------------------
    inline volScalarFieldHolder surfaceSum( const surfaceScalarFieldHolder& field )
    {
      return volScalarFieldHolder( surfaceSum( field() ), createArgs( field ) );
    }


    //---------------------------------------------------------------------------
    inline volVectorFieldHolder grad( const surfaceScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), createArgs( field ) );
    }
    
    inline volVectorFieldHolder grad( const volScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), createArgs( field ) );
    }


    //---------------------------------------------------------------------------
    inline surfaceScalarFieldHolder ddtPhiCorr( const volScalarFieldHolder& rA,
                                                const volVectorFieldHolder& U,
                                                const surfaceScalarFieldHolder& phi )
    {
      return surfaceScalarFieldHolder( ddtPhiCorr( rA(), U(), phi() ), createArgs( rA, U, phi ) );
    }                   
    

    //---------------------------------------------------------------------------
    inline volScalarFieldHolder div( const surfaceScalarFieldHolder& phi )
    {
      return volScalarFieldHolder( div( phi() ), createArgs( phi ) );
    }                   
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
