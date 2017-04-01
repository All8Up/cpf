# ###############################################
set (INCLUDE_FILES
	Include/COM.hpp
	Include/COM/iUnknown.hpp
)

add_library (COM INTERFACE
)
target_link_libraries (COM INTERFACE Configuration RefCount)

target_include_directories (COM INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
source_group (Interface FILES ${INCLUDE_FILES})

add_custom_target (COM_IDE SOURCES ${INCLUDE_FILES})
set_property (TARGET COM_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})

install( DIRECTORY Include/Core
	DESTINATION Include/Core
	PATTERN *
)


install (TARGETS COM
	EXPORT COMConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT COMConfig DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY COM GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
