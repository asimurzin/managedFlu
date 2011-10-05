//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
void rhoEqn( const volScalarFieldHolder& rho, const surfaceScalarFieldHolder& phi )
{
  solve( fvm::ddt( rho ) + fvc::div( phi ) );
}

