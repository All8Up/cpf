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
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})

set_property (TARGET s_ANSI_C_FileSystem PROPERTY FOLDER Libraries/Static/Adapter)

# ###############################################
MakeUnitTests (LIBRARY ANSI_C_FileSystem:static GROUP Adapter
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
)
