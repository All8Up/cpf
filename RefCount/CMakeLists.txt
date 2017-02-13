# ###############################################
set( INCLUDE_FILES
	Include/RefCount.hpp
	Include/RefCounted.hpp
	Include/IntrusivePtr.hpp
)
set( SOURCE_FILES
	Source/RefCount.cpp
)

add_library( s_RefCount STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_RefCount
	PUBLIC CPF_STATIC_REFCOUNT
	PRIVATE CPF_BUILD_REFCOUNT
)
add_library( RefCount SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( RefCount
	PRIVATE CPF_BUILD_REFCOUNT
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( RefCount Configuration )
target_link_libraries( s_RefCount Configuration )

target_include_directories( RefCount PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
target_include_directories( s_RefCount PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_RefCount PROPERTY FOLDER Libraries/Static/Core )
set_property( TARGET RefCount PROPERTY FOLDER Libraries/Shared/Core )

install( DIRECTORY Include/Core
	DESTINATION Include/Core
	PATTERN *
)


install( TARGETS RefCount
	EXPORT RefCountConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_RefCount
	EXPORT RefCountConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT RefCountConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY RefCount GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
