# ###############################################
# Setup the project.
cmake_minimum_required (VERSION 3.5.1)
cmake_policy (SET CMP0054 NEW)

# ###############################################
project (CPF C CXX CSharp)

# ###############################################
include ("${CMAKE_CURRENT_LIST_DIR}/CMake/Setup.cmake")

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Core")


# ###############################################
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Application")
