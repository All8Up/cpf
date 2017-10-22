# ###############################################
set (INCLUDE_FILES
	Include/Future.hpp
)

add_library (Future INTERFACE
)
target_link_libraries (Future INTERFACE Configuration)

source_group (Interface FILES ${INCLUDE_FILES})

target_include_directories (Future INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

add_custom_target (Future_IDE SOURCES ${INCLUDE_FILES})
set_property (TARGET Future_IDE PROPERTY FOLDER Libraries/Interface/Platform)
source_group (Interface FILES ${INCLUDE_FILES})

install( DIRECTORY Include
	DESTINATION Include
	PATTERN *
)


install (TARGETS Future
	EXPORT FutureConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT FutureConfig DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY Future GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
)
