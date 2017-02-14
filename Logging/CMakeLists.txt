#
set (INCLUDE_FILES
	Include/Logging/Logging.hpp
)

add_library (Logging INTERFACE)
target_include_directories (Logging
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${CPF_PLATFORM_INCLUDE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

target_link_libraries( Logging INTERFACE Configuration spdlog )

add_custom_target (Logging_IDE SOURCES ${INCLUDE_FILES} )
set_property (TARGET Logging_IDE PROPERTY FOLDER Libraries/Interface/Diagnostics)
source_group (Include FILES ${INCLUDE_FILES})


# Installation setup.
install (DIRECTORY Include/Logging
	DESTINATION Include/Logging
	PATTERN *
)

#[[
install( TARGETS Logging
	EXPORT LoggingConfiguration
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)

install( EXPORT LoggingConfiguration DESTINATION CMake )
]]#

# ###############################################
MakeUnitTest( LIBRARY Logging GROUP Diagnostics
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		Logging Configuration
)
