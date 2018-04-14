# ###############################################
# Setup the project.
cmake_minimum_required (VERSION 3.5.1)
cmake_policy (SET CMP0054 NEW)

# ###############################################
project (CPF C CXX CSharp)

# ###############################################
set (CPF_OS_BIN_DIR "${CMAKE_CURRENT_LIST_DIR}/CPF/Bin/Windows")
set (CPF_EXTERNAL_ROOT "${CMAKE_CURRENT_LIST_DIR}/3rdParty")

# ###############################################
# NOTE: this is an 'include' rather than
# 'add_subdirectory', it allows CPF to setup the
# build environment for other items such as the
# examples found below.
include (CPF/CMakeLists.txt)

# ###############################################
if (EXISTS ${CPF_EXTERNAL_ROOT}/CMakeLists.txt)
	add_subdirectory (${CPF_EXTERNAL_ROOT})
endif ()
if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/Plugins/CMakeLists.txt)
	add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Plugins")
endif ()
