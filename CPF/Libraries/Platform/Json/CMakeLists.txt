# ###############################################
set( INCLUDE_FILES
	Include/Json/Json.hpp
)
set( SOURCE_FILES
	Source/Json.cpp
)

add_library( s_Json STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_Json
	PUBLIC CPF_STATIC_JSON
	PRIVATE CPF_BUILD_JSON
)
add_library( Json SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( Json
	PRIVATE CPF_BUILD_JSON
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( Json Configuration Collections rapidjson )
target_link_libraries( s_Json Configuration s_Collections rapidjson )

target_include_directories( Json
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_include_directories( s_Json
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Json PROPERTY FOLDER Libraries/Static/Platform )
set_property( TARGET Json PROPERTY FOLDER Libraries/Shared/Platform )

install( DIRECTORY Include/Json
	DESTINATION Include/Json
	PATTERN *
)

install( TARGETS Json
	EXPORT JsonConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_Json
	EXPORT JsonConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT JsonConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY Json GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		../../Core/Test/UnitTestMain.cpp
)
