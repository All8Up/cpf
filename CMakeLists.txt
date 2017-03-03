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
# Setup for tools build.
find_package (Qt5Widgets)
if (Qt5Widgets)
	# With Qt found, include tools.
endif ()
