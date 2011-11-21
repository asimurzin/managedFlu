//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
//  Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  See http://sourceforge.net/projects/pythonflu
//
//  Author : Alexey PETROV, Andrey Simurzin


//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
argList setRootCase( int argc, char *argv[] )
{
  argList args(argc, argv);
  if (!args.checkRootCase())
  {
    FatalError.exit();
  }
  
  return args;
}

//---------------------------------------------------------------------------
TimeHolder createTime(  const word& dict_name, const argList& args )
{
  Info<< "Create time\n" << endl;
      
  return TimeHolder( dict_name, args);
} 


//---------------------------------------------------------------------------
fvMeshHolder createMesh( const TimeHolder& runTime )
{
  Info << "Create mesh for time = "  << runTime->timeName() << nl << endl;
  return fvMeshHolder( IOobjectHolder( fvMesh::defaultRegion,
                                             runTime->timeName(),
                                             runTime,
                                             IOobject::MUST_READ ) );
} 


//---------------------------------------------------------------------------
fvMeshHolder createMeshNoClear( const TimeHolder& runTime )
{
  Info << "Create mesh, no clear-out for time = "  << runTime->timeName() << nl << endl;
  return fvMeshHolder( IOobjectHolder( fvMesh::defaultRegion,
                                             runTime->timeName(),
                                             runTime,
                                             IOobject::MUST_READ ) );
} 


//---------------------------------------------------------------------------
