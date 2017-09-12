# ###############################################
set (INCLUDE_FILES
	Include/GOM.hpp
	Include/GOM/Types.hpp
	Include/GOM/iUnknown.hpp
	Include/GOM/Result.hpp
	Include/GOM/ResultCodes.hpp
)

add_library (GOM INTERFACE)
target_link_libraries (GOM INTERFACE Configuration RefCount)

target_include_directories (GOM INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
source_group (Interface FILES ${INCLUDE_FILES})

add_custom_target (GOM_IDE SOURCES ${INCLUDE_FILES})
set_property (TARGET GOM_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})

install( DIRECTORY Include/Core
	DESTINATION Include/Core
	PATTERN *
)


install (TARGETS GOM
	EXPORT GOMConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT GOMConfig DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY GOM GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
