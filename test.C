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
Foam::IOobjectHolder create_IOobject( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
  
  Foam::Info << "Create mesh IObject for time = " << runTime->timeName() << Foam::nl << Foam::endl;
      
  return  Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
	                        runTime->timeName(),
		                runTime,
				Foam::IOobject::MUST_READ );
}


//-----------------------------------------------------------------------------
Foam::fvMeshHolder create_mesh( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
  
  Foam::Info << "Create mesh for time = " << runTime->timeName() << Foam::nl << Foam::endl;
      
  return  Foam::fvMeshHolder( Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
				                    runTime->timeName(),
						    runTime,
						    Foam::IOobject::MUST_READ ) );
}



Foam::fvMeshHolder create_mesh( const Foam::TimeHolder& runTime )
{
  Foam::Info << "Create mesh for time = " << runTime->timeName() << Foam::nl << Foam::endl;
      
  return  Foam::fvMeshHolder( Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
				                    runTime->timeName(),
						    runTime,
						    Foam::IOobject::MUST_READ ) );
}

//-----------------------------------------------------------------------------
Foam::IOdictionaryHolder create_IOdictionary( const Foam::word& dict_name, const Foam::argList& args )
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
  
  Foam::fvMeshHolder mesh = create_mesh( runTime );
  
  return IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                             runTime->constant(),
                                             mesh,
                                             Foam::IOobject::MUST_READ_IF_MODIFIED,
                                             Foam::IOobject::NO_WRITE ) );
}  

//-----------------------------------------------------------------------------
/*Foam::volScalarFieldHolder test_func( const Foam::word& dict_name, const Foam::argList& args)
{
  Foam::TimeHolder runTime = create_time( dict_name, args );
   
  Foam::fvMeshHolder mesh =  create_mesh( runTime );
  
  Foam::Info << "Reading field p\n" << endl;
  return Foam::volScalarFieldHolder( IOobject( "p",
                                               runTime->timeName(),
                                               *mesh,
                                               IOobject::MUST_READ,
                                               IOobject::AUTO_WRITE ),
                                               mesh );
}*/


//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    Foam::argList args(argc, argv);
    if (!args.checkRootCase())
    {
        Foam::FatalError.exit();
    }

    Foam::fvMeshHolder ioh = create_mesh( Foam::Time::controlDictName, args );
    
    Info<< nl << nl << "Reading transportProperties\n" << endl;
    Foam::IOdictionaryHolder iodh = create_IOdictionary( Foam::Time::controlDictName, args );
    dimensionedScalar nu( iodh->lookup("nu") );
    
    Info << endl << "Reading from IOdictionary -> nu.value = " << nu.value() << 
                     "     nu.dimen = " << nu.dimensions() << nl << nl;

    
    /*Foam::volScalarFieldHolder field=test_func( Foam::Time::controlDictName, args );
       
    Foam::Info << nl <<"FIELD =" << *field << endl;
    cout << "Before the main finish" << nl;*/
    
    return 0;
    
}


// ************************************************************************* //
