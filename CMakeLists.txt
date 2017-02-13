# ###############################################
# Setup the project.
cmake_minimum_required( VERSION 3.5.1 )
cmake_policy(SET CMP0054 NEW)


# ###############################################
project( Cpf C CXX )


# ###############################################
include( CMake/Setup.cmake )


# ###############################################
# Find the external directory.
set (EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/External)
if (EXISTS "${EXTERNAL_DIR}" AND IS_DIRECTORY "${EXTERNAL_DIR}")
	# The external directory has been copied into the project.
	add_subdirectory (${EXTERNAL_DIR}/cmake)
else ()
	message ("No external libraries found.")
endif ()


# ###############################################
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Cpf")
	add_subdirectory( Cpf )

	# ###############################################
	install( EXPORT Cpf DESTINATION CMake )
	install( FILES Sdk/CMakeLists.txt
		DESTINATION ./
	)
else ()
	message ("No CPF library sources found.")
endif ()
