/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2010 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    icoFoam

Description
    Transient solver for incompressible, laminar flow of Newtonian fluids.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "IOobjectHolder.H"
#include "TimeHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"
#include "IOdictionaryHolder.H"
#include "volScalarFieldHolder.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
Foam::TimeHolder create_time(  const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::Info<< "Create time\n" << Foam::endl;
      
  return Foam::TimeHolder( dict_name, args);

} 


//-----------------------------------------------------------------------------
Foam::fvMeshHolder create_mesh( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
  
  return  Foam::fvMeshHolder( Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
				                    runTime->timeName(),
						    runTime,
						    Foam::IOobject::MUST_READ ) );
}

//-------------------

void testing_mesh( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::fvMeshHolder  mesh = create_mesh( dict_name, args );
}

//-----------------------------------------------------------------------------
Foam::IOdictionaryHolder create_IOdictionary( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
  
  Foam::fvMeshHolder mesh( Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
				                 runTime->timeName(),
						 runTime,
						 Foam::IOobject::MUST_READ ) );
  
  return IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                             runTime->constant(),
                                             mesh,
                                             Foam::IOobject::MUST_READ_IF_MODIFIED,
                                             Foam::IOobject::NO_WRITE ) );
}  


//---------------
void testing_IOdictionary( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::IOdictionaryHolder iodh = create_IOdictionary( dict_name, args );
 
  dimensionedScalar nu( iodh->lookup("nu") );
    
  Info << endl << "Reading from IOdictionary -> nu.value = " << nu.value() << 
                    "     nu.dimen = " << nu.dimensions() << nl << nl;

}


//-----------------------------------------------------------------------------
Foam::volScalarFieldHolder creating_field( const Foam::word& dict_name, const Foam::argList& args)
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
  
  Foam::fvMeshHolder mesh( Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
				                 runTime->timeName(),
						 runTime,
						 Foam::IOobject::MUST_READ ) );
 
  Foam::Info << "Reading field p\n" << endl;
  
  return Foam::volScalarFieldHolder( IOobjectHolder( "p",
                                               runTime->timeName(),
                                               mesh,
                                               IOobject::MUST_READ,
                                               IOobject::AUTO_WRITE ),
                                               mesh );
}


//---------------
void testing_field( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::volScalarFieldHolder field = creating_field( dict_name, args );
  Info << *field << endl;
  Foam::volScalarFieldHolder field1 = field + field;
  Info << *field1 << endl;
}  


//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    Foam::argList args(argc, argv);
    if (!args.checkRootCase())
    {
        Foam::FatalError.exit();
    }
    Info << "------------------------------------------------" << endl;
    Info << "   Testing fvMesh\n" << endl;
    Info << "------------------------------------------------" << endl;
    testing_mesh( Foam::Time::controlDictName, args );
    
    Info<< "\n------------------------------------------------" << endl;
    
    
    Info<< "   Testing IOdictionary" << endl;
    Info << "------------------------------------------------" << endl;
    
    testing_IOdictionary( Foam::Time::controlDictName, args );
    
    Info << "\n------------------------------------------------" << endl;
    
    Info<< "   Testing volScalarField" << endl;
    Info << "------------------------------------------------" << endl;
    
    testing_field( Foam::Time::controlDictName, args );
    
    Info << "------------------------------------------------\n" << endl;
    
    return 0;
    
}


// ************************************************************************* //
