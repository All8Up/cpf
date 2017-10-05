# ###############################################
# Setup the project.
cmake_minimum_required( VERSION 3.5.1 )
cmake_policy(SET CMP0054 NEW)

# ###############################################
project( Cpf C CXX )

# ###############################################
include( CMake/Setup.cmake )

# ###############################################
set (CPF_USE_DXGI1_2 ${HAVE_DXGI1_2})
set (CPF_USE_DXGI1_3 ${HAVE_DXGI1_3})
set (CPF_USE_DXGI1_4 ${HAVE_DXGI1_4})

# ###############################################
# Find the external directory.
set (EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/External)
if (EXISTS "${EXTERNAL_DIR}" AND IS_DIRECTORY "${EXTERNAL_DIR}")
	# The external directory has been copied into the project.
	add_subdirectory (${EXTERNAL_DIR})
else ()
	message ("No external libraries found.")
endif ()

# ###############################################
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Cpf")
	add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Cpf" )
else ()
	message ("No CPF library sources found.")
endif ()

# ###############################################
set (CPF_BUILD_EXPERIMENTAL ON CACHE BOOL "Build experimental work.")
if (CPF_BUILD_EXPERIMENTAL)
	if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Experimental")
		add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Experimental" )
	else ()
		message ("No experimental sources found.")
	endif ()
endif ()

# ###############################################
set (CPF_BUILD_KPI ON CACHE BOOL "Build KPI's.")
if (CPF_BUILD_KPI)
	if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/KPI")
		add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/KPI" )
	else ()
		message ("No KPI sources found.")
	endif ()
endif ()

# ###############################################
set (CPF_BUILD_TOOLS ON CACHE BOOL "Build tools.")
if (CPF_BUILD_TOOLS)
	if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tools")
		add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Tools" )
	else ()
		message ("No tool sources found.")
	endif ()
endif ()
