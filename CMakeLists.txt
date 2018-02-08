# ###############################################
# Setup the project.
cmake_minimum_required (VERSION 3.5.1)
cmake_policy (SET CMP0054 NEW)

# ###############################################
project (CPF C CXX CSharp)

# ###############################################
include ("${CMAKE_CURRENT_LIST_DIR}/CMake/Setup.cmake")

# ###############################################
option (CPF_ENABLE_CSHARP "Enable C# integration." OFF)
option (CPF_ENABLE_DEVBUILD "Enable the development build." ON)
if (CPF_ENABLE_CSHARP)
	add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/CSBinding")
	set (CPF_EXTRA_LIBS "${CPF_EXTRA_LIBS};CSBinding")
	set (CPF_CS_LIBS "CSBinding")
endif ()

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Core")

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Application")
