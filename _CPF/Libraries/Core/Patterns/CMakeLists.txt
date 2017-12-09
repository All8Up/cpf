# ###############################################
set (INCLUDE_FILES
	Include/Patterns.hpp
	Include/Patterns/Factory.hpp
)

add_library (Patterns INTERFACE)
target_link_libraries (Patterns INTERFACE Configuration s_Collections)

target_include_directories (Patterns INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

add_custom_target (Patterns_IDE SOURCES ${INCLUDE_FILES} )
set_property (TARGET Patterns_IDE PROPERTY FOLDER Libraries/Interface/Core)

source_group (Interface FILES ${INCLUDE_FILES})

install (TARGETS Patterns
	EXPORT PatternsConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT PatternsConfig DESTINATION CMake)


MakeUnitTest (LIBRARY Patterns GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Factory.cpp
		../Test/UnitTestMain.cpp
)
