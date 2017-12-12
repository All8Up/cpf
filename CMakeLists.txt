# ###############################################
# Setup the project.
cmake_minimum_required (VERSION 3.5.1)
cmake_policy (SET CMP0054 NEW)

# ###############################################
project (CPF C CXX CSharp)

# ###############################################
include (CMake/Setup.cmake)

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/CPF")

# ###############################################
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Application")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Application")
endif ()

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Graphics")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Graphics")
endif ()

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Examples")
	add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Examples")
endif ()
