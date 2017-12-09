# ###############################################
configure_file (Include/CPF/Configuration/Setup.hpp.in
	${CPF_GENERATED}/CPP/CPF/Configuration/Setup.hpp )

# ###############################################
set (INCLUDE_FILES
	Include/CPF/Configuration.hpp
)
set (INCLUDE_CONFIGURATION_FILES
	Include/CPF/Configuration/Macros.hpp
	Include/CPF/Configuration/Setup.hpp.in
	${CMAKE_BINARY_DIR}/CPF/Configuration/Setup.hpp
)
set (SOURCE_FILES
	Source/CPF.cpp
)

# ###############################################
set (IDL_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/GOM/ResultCodes.idl
)

# ###############################################
CPF_GEN_GOM(CppGOMFiles cpp
	hpp
	${CPF_GENERATED}/CPP/CPF/GOM
	${IDL_FILES}
)

# ###############################################
add_library (CPF STATIC
	${INCLUDE_FILES}
	${INCLUDE_CONFIGURATION_FILES}
	${SOURCE_FILES}
	${CppGOMFiles}
)
target_include_directories (CPF
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<BUILD_INTERFACE:${CPF_GENERATED}/CPP>
)
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Configuration FILES ${INCLUDE_CONFIGURATION_FILES})
source_group (Sources FILES ${SOURCE_FILES})
set_property (TARGET CPF PROPERTY FOLDER Core)

# ###############################################
install (TARGETS CPF
	EXPORT CPFConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT CPFConfig DESTINATION CMake)

# ###############################################
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/Libraries")

set (CPF_BUILD_TOOLS ON CACHE BOOL "Build tools.")
if (CPF_BUILD_TOOLS)
	add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Tools" )
endif ()
