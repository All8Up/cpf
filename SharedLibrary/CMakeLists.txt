# ###############################################
set( INCLUDE_FILES
	Include/${CPF_TARGET_OS}/Platform/SharedLibrary.hpp
	Include/SharedLibrary/SharedLibrary.hpp
)
set( SOURCE_FILES
	Source/SharedLibrary.cpp
)

add_library( s_SharedLibrary STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_SharedLibrary
	PUBLIC CPF_STATIC_SHAREDLIBRARY
	PRIVATE CPF_BUILD_SHAREDLIBRARY
)
add_library( SharedLibrary SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( SharedLibrary
	PRIVATE CPF_BUILD_SHAREDLIBRARY
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( SharedLibrary Configuration RefCount Collections Logging )
target_link_libraries( s_SharedLibrary Configuration RefCount s_Collections Logging )

target_include_directories( SharedLibrary PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}>
)
target_include_directories( s_SharedLibrary PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}>
)

set_property( TARGET s_SharedLibrary PROPERTY FOLDER Libraries/Static/Platform )
set_property( TARGET SharedLibrary PROPERTY FOLDER Libraries/Shared/Platform )

install( DIRECTORY Include/SharedLibrary
	DESTINATION Include/SharedLibrary
	PATTERN *
)

#[[
install( TARGETS SharedLibrary
	EXPORT SharedLibraryConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_SharedLibrary
	EXPORT SharedLibraryConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT SharedLibraryConfig DESTINATION CMake )
]]#

# ###############################################
MakeUnitTests( LIBRARY SharedLibrary GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
)
