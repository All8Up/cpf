# ###############################################
# Setup the project.
cmake_minimum_required (VERSION 3.5.1)
cmake_policy (SET CMP0054 NEW)

# ###############################################
include ("${CMAKE_CURRENT_LIST_DIR}/CMake/Setup.cmake")

# ###############################################
option (CPF_ENABLE_CSHARP "Enable C# integration." OFF)
option (CPF_ENABLE_DEVBUILD "Enable the development build." ON)
option (CPF_BUILD_EXAMPLES "Enable example projects." ON)
option (CPF_BUILD_EXPERIMENTAL "Enable experimental projects." ON)
option (CPF_BUILD_KPI "Enable KPI projects." ON)
option (CPF_ENABLE_PACKAGING "Enable packaging targets." OFF)
if (CPF_ENABLE_CSHARP)
	add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/CSBinding")
	set (CPF_EXTRA_LIBS "${CPF_EXTRA_LIBS};CSBinding")
	set (CPF_CS_LIBS "CSBinding")
endif ()

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/ICore")
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Core")

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Application")

# ###############################################
if (CPF_BUILD_EXAMPLES)
	add_subdirectory ("${CMAKE_CURRENT_LIST_DIR}/Examples")
endif ()
