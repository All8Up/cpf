# ###############################################
set (INCLUDE_FILES
	Include/CPF/Configuration.hpp
)
set (INCLUDE_CONFIGURATION_FILES
	Include/CPF/Configuration/Macros.hpp
)
set (SOURCE_FILES
	Source/CPF.cpp
)

add_library (CPF STATIC
	${INCLUDE_FILES}
	${INCLUDE_CONFIGURATION_FILES}
	${SOURCE_FILES}
)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Configuration FILES ${INCLUDE_CONFIGURATION_FILES})
source_group (Sources FILES ${SOURCE_FILES})
set_property (TARGET CPF PROPERTY FOLDER Core)

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Libraries")

set (CPF_BUILD_TOOLS ON CACHE BOOL "Build tools.")
if (CPF_BUILD_TOOLS)
	add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Tools" )
endif ()
