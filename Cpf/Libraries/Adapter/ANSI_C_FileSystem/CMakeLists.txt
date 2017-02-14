# ###############################################
set (INCLUDE_FILES
	Include/Adapter/FileSystem.hpp
)
set (SOURCE_FILES
	Source/FileSystem.cpp
)

# ###############################################
add_library (s_ANSI_C_FileSystem STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (s_ANSI_C_FileSystem
	PUBLIC CPF_STATIC_ANSI_C_FILESYSTEM
	PRIVATE CPF_BUILD_ANSI_C_FILESYSTEM
)
target_compile_definitions (s_ANSI_C_FileSystem
	PRIVATE CPF_BUILD_SDL2
)
target_link_libraries (s_ANSI_C_FileSystem Configuration s_Collections s_IO Logging)

target_include_directories (s_ANSI_C_FileSystem
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_include_directories (s_ANSI_C_FileSystem
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
#[[
add_library (ANSI_C_FileSystem STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions (ANSI_C_FileSystem
	PUBLIC CPF_STATIC_ANSI_C_FILESYSTEM
	PRIVATE CPF_BUILD_ANSI_C_FILESYSTEM
)
target_compile_definitions (ANSI_C_FileSystem
	PRIVATE CPF_BUILD_SDL2
)
target_link_libraries (ANSI_C_FileSystem Configuration s_Collections IO Logging)

target_include_directories (ANSI_C_FileSystem
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_include_directories (ANSI_C_FileSystem
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
#]]

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

set_property (TARGET s_ANSI_C_FileSystem PROPERTY FOLDER Libraries/Static/Adapter)
#set_property (TARGET ANSI_C_FileSystem PROPERTY FOLDER Libraries/Shared/Adapter)

#[[
install (DIRECTORY Include/Adapter
	DESTINATION Include/Adapter
	PATTERN *
)

install (TARGETS s_ANSI_C_FileSystem
	EXPORT ANSI_CFileSystemConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)

install (TARGETS ANSI_C_FileSystem
	EXPORT ANSI_CFileSystemConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)

install (EXPORT ANSI_CFileSystemConfig DESTINATION CMake)
#]]

# ###############################################
MakeUnitTests (LIBRARY ANSI_C_FileSystem:static GROUP Adapter
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		PlatformLib:static
)
