# managedFlu - OpenFOAM C++ interactive functionality API
# Copyright (C) 2010- Alexey Petrov
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# See http://sourceforge.net/projects/pythonflu
#
# Author : Alexey PETROV, Andrey Simurzin


#--------------------------------------------------------------------------------------
DESTDIR=

MANAGED_FLU_LIB=$(DESTDIR)/usr/local/lib
MANAGED_FLU_BIN=$(DESTDIR)/usr/local/bin
MANAGED_FLU_INCLUDE=$(DESTDIR)/usr/local/include/managedFlu
MANAGED_FLU_M4=$(DESTDIR)/usr/local/share/managedFlu

install: $(MANAGED_FLU_LIB) $(MANAGED_FLU_BIN)/laplacianFoamMF $(MANAGED_FLU_INCLUDE) $(MANAGED_FLU_M4)
	@ echo "That's all"

$(MANAGED_FLU_LIB): 
	@ install -d $(MANAGED_FLU_LIB)
	@ cp -rf lib/* $(MANAGED_FLU_LIB)

$(MANAGED_FLU_BIN)/laplacianFoamMF:
	@ install -d $(MANAGED_FLU_BIN)
	@ cp -rf bin/* $(MANAGED_FLU_BIN)

$(MANAGED_FLU_INCLUDE): 
	@ install -d $(MANAGED_FLU_INCLUDE)
	@ cp -rf include/libs $(MANAGED_FLU_INCLUDE)

$(MANAGED_FLU_M4): 
	@ install -d $(MANAGED_FLU_M4)/admin
	@ cp -rf admin $(MANAGED_FLU_M4)


#--------------------------------------------------------------------------------------     	 
