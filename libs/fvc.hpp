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
      return volScalarFieldHolder( surfaceSum( field() ), deps( &field ) );
    }


    //---------------------------------------------------------------------------
    inline volVectorFieldHolder grad( const surfaceScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), deps( &field ) );
    }
    
    inline volVectorFieldHolder grad( const volScalarFieldHolder& field )
    {
      return volVectorFieldHolder( grad( field() ), deps( &field ) );
    }


    //---------------------------------------------------------------------------
    inline surfaceScalarFieldHolder ddtPhiCorr( const volScalarFieldHolder& rA,
                                                const volVectorFieldHolder& U,
                                                const surfaceScalarFieldHolder& phi )
    {
      return surfaceScalarFieldHolder( ddtPhiCorr( rA(), U(), phi() ), deps( &rA, deps( &U, &phi ) ) );
    }                   
    

    //---------------------------------------------------------------------------
    inline volScalarFieldHolder div( const surfaceScalarFieldHolder& phi )
    {
      return volScalarFieldHolder( div( phi() ), deps( &phi ) );
    }
    
    
    //---------------------------------------------------------------------------
    inline surfaceScalarFieldHolder snGrad( const volScalarFieldHolder& field)
    {
      return surfaceScalarFieldHolder( snGrad( field() ), deps( &field ) );
    }

    inline surfaceScalarFieldHolder snGrad( const volScalarFieldHolder& field, const word& name)
    {
      return surfaceScalarFieldHolder( snGrad( field(), name ), deps( &field ) );
    }

   //---------------------------------------------------------------------------
   inline volVectorFieldHolder reconstruct( const surfaceScalarFieldHolder& field )
    {
      return volVectorFieldHolder( reconstruct( field() ), deps( &field ) );
    }

                   
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
