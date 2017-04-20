# ###############################################
set (INCLUDE_FILES
	Include/RefCount.hpp
	Include/RefCounted.hpp
	Include/IntrusivePtr.hpp
)

add_library (RefCount INTERFACE
)
target_link_libraries (RefCount INTERFACE Configuration Hash)

source_group (Interface FILES ${INCLUDE_FILES})

target_include_directories (RefCount INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

add_custom_target (RefCount_IDE SOURCES ${INCLUDE_FILES})
set_property (TARGET RefCount_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})

install( DIRECTORY Include/Core
	DESTINATION Include/Core
	PATTERN *
)


install (TARGETS RefCount
	EXPORT RefCountConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT RefCountConfig DESTINATION CMake )


# ###############################################
MakeUnitTest (LIBRARY RefCount GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
