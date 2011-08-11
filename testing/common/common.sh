## VulaSHAKA (Simultaneous Neutronic, Fuel Performance, Heat And Kinetics Analysis)
## Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
## 
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
## 
## See https://vulashaka.svn.sourceforge.net/svnroot/vulashaka
##
## Author : Alexey PETROV


#------------------------------------------------------------------------------
get_foam_version()
{
  echo 020000
}


#------------------------------------------------------------------------------
bypassCases()
{
  engine=$1
 
  list_versions="r1.6-dev r1.5-dev r1.4.1-dev"
  
  current_version=`echo ${list_versions} | awk -F" " '{print $1}'`
  cases_file=${PYFOAM_TESTING_DIR}/cases/${current_version}/cases_file
  
  list_cases=`cat ${cases_file}`
  
  cases_folder=${PYFOAM_TESTING_DIR}/cases
  
  for case in ${list_cases} ;do
     for version in ${list_versions}; do
         case_folder=${cases_folder}/${version}/${case}
         if [ -f ${case_folder}/${engine} ]; then
            echo "Visiting : ${case_folder}"
            echo ------------------------------------------------------------------------------
            echo
            ( cd ${case_folder} && ./${engine} )
            echo
            echo ------------------------------------------------------------------------------
            break
         fi
     done
  done    

}


#------------------------------------------------------------------------------
bypassCases1()
{
  engine=$1
  if [ -d local/r${WM_PROJECT_VERSION} ]; then
     ( cd local/r${WM_PROJECT_VERSION} && runRecursive ${engine} )
  fi
  
  list_cases="r1.6-dev r1.5-dev r1.4.1-dev"

  for case in ${list_cases} ;do
     if [ -d ${case} ]; then
        ( cd ${case} && runRecursive ${engine} )
     fi
  done
}



#-------------------------------------------------------------------------------
runRecursive()
{
  engine=$1
  if [ -f ${engine} ]; then
    echo ------------------------------------------------------------------------------
    echo
    ./${engine}
    echo
    echo ------------------------------------------------------------------------------
  else
     for case in *; do
        if [ -d ${case} ]; then
           ( cd ${case} && echo Visiting : `pwd` && runRecursive ${engine} )
        fi
     done
  fi   
}


#------------------------------------------------------------------------------
get_source_case ()
{
    dir=`pwd` 
    if [ $# -gt 0 ] ; then
       dir=${dir}/${1}
    fi
    echo ${dir}
}


#------------------------------------------------------------------------------
get_reference_case ()
{
   source_case=`get_source_case $*`
   echo ${source_case}_reference
}


#------------------------------------------------------------------------------
diff_two_cases ()
{
   source_case=${1}
   reference_case=${2}
   echo ------------- differencing with the referenced C++ solver -------------
   diff -r -q -I "case" -x ".svn" -x "All*" -x "log.*" ${reference_case} ${source_case} 
   echo -----------------------------------------------------------------------
}


#------------------------------------------------------------------------------
