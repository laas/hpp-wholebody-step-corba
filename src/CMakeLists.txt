# Copyright (c) 2011 CNRS
# Author: Florent Lamiraux
#
# This file is part of hpp-wholebody-step-corba.
# hpp-wholebody-step-corba is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# hpp-wholebody-step-corba is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# hpp-wholebody-step-corba.  If not, see
# <http://www.gnu.org/licenses/>.

SET(IDL_SOURCES
  wholebody_step)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src)
FOREACH(IDL ${IDL_SOURCES})
  GENERATE_IDL_FILE (${IDL}
    ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/wholebody-step)
ENDFOREACH()

SET(LIBRARY_NAME ${PROJECT_NAME})
ADD_LIBRARY(${LIBRARY_NAME}
  SHARED
  server.cc
  wholebody_step.impl.hh
  wholebody_step.impl.cc
  wholebody_stepSK.cc
  ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/wholebody_step/wholebody_step_idl.py
)

PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} hpp-wholebody-step-planner)
PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} hpp-template-corba)
PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} hpp-util)

INSTALL(TARGETS ${LIBRARY_NAME} DESTINATION lib)

# search for python
FINDPYTHON()

# search for omniidl
FIND_PROGRAM(OMNIIDL omniidl)
IF(${OMNIIDL} STREQUAL OMNIIDL-NOTFOUND)
  MESSAGE(FATAL_ERROR "cannot find omniidl.")
ENDIF(${OMNIIDL} STREQUAL OMNIIDL-NOTFOUND)

FOREACH (IDL ${IDL_SOURCES})
  ADD_CUSTOM_COMMAND(
    OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/wholebody_step/${IDL}_idl.py
    COMMAND ${OMNIIDL}
    ARGS -bpython -Wbpackage="hpp.corbaserver.wholebody_step"
    ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/wholebody-step/${IDL}.idl
    MAIN_DEPENDENCY
    ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/wholebody-step/${IDL}.idl
    )
  SET_SOURCE_FILES_PROPERTIES(
    ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/wholebody_step/${IDL}_idl.py
    GENERATED=ON
    )
  INSTALL(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/wholebody_step/${IDL}_idl.py
    DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/wholebody_step
    )
ENDFOREACH()
INSTALL(
  FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/hpp/corbaserver/wholebody_step/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/wholebody_step
  )
INSTALL(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/wholebody_step/hpp/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/wholebody_step/hpp
  )
INSTALL(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/wholebody_step/hpp__POA/__init__.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/wholebody_step/hpp__POA
  )
INSTALL(
  FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/hpp/corbaserver/wholebody_step/client.py
  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/wholebody_step
  )
