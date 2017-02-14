# ###############################################
set( INCLUDE_FILES
	Include/Hash/Hash.hpp
	Include/Hash/Crc.hpp
	Include/Hash/Detail/Crc16Table.hpp
	Include/Hash/Detail/Crc32Table.hpp
	Include/Hash/Detail/Crc64Table.hpp
)
set( SOURCE_FILES
	Source/Hash.cpp
)

add_library( s_Hash STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( s_Hash
	PUBLIC CPF_STATIC_HASH
	PRIVATE CPF_BUILD_HASH
)
add_library( Hash SHARED
	${INCLUDE_FILES}
	${SOURCE_FILES}
)
target_compile_definitions( Hash
	PRIVATE CPF_BUILD_HASH
)
source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )

target_link_libraries( Hash Configuration )
target_link_libraries( s_Hash Configuration )

target_include_directories( Hash PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
target_include_directories( s_Hash PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Hash PROPERTY FOLDER Libraries/Static/Platform )
set_property( TARGET Hash PROPERTY FOLDER Libraries/Shared/Platform )

install( DIRECTORY Include/Hash
	DESTINATION Include/Hash
	PATTERN *
)


install( TARGETS Hash
	EXPORT HashConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( TARGETS s_Hash
	EXPORT HashConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT HashConfig DESTINATION CMake )


# ###############################################
MakeUnitTests( LIBRARY Hash GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Crc.hpp
		../../Core/Test/UnitTestMain.cpp
)
