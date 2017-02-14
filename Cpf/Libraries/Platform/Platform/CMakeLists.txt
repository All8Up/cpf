# ###############################################
set (INCLUDE_FILES
	Include/Cpf/Platform.hpp
)
set (SOURCE_FILES
	Source/Platform.cpp
)

# ###############################################
add_library (s_PlatformLib STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (s_PlatformLib
	PUBLIC CPF_STATIC_PLATFORM
	PRIVATE CPF_BUILD_PLATFORM
)
target_compile_definitions (s_PlatformLib
	PRIVATE CPF_BUILD_PLATFORM
)
target_link_libraries (s_PlatformLib
	Configuration
	s_Events
	s_Hash
	s_IO
	s_Json
	s_SharedLibrary
	s_Threading
	s_Time
)
target_include_directories (s_PlatformLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_include_directories (s_PlatformLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
add_library (PlatformLib STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (PlatformLib
	PUBLIC CPF_STATIC_PLATFORM
	PRIVATE CPF_BUILD_PLATFORM
)
target_compile_definitions (PlatformLib
	PRIVATE CPF_BUILD_PLATFORM
)
target_link_libraries (PlatformLib
	Configuration
	Events
	Hash
	IO
	Json
	SharedLibrary
	Threading
	Time
)
target_include_directories (PlatformLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_include_directories (PlatformLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

set_property (TARGET PlatformLib PROPERTY FOLDER Libraries/Shared)
set_property (TARGET s_PlatformLib PROPERTY FOLDER Libraries/Static)

source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

#[[
install (DIRECTORY Include/Cpf
	DESTINATION Include/Cpf
	PATTERN *
)

install (TARGETS s_PlatformLib
	EXPORT PlatformConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (TARGETS PlatformLib
	EXPORT PlatformConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT PlatformConfig DESTINATION CMake)
]]#
