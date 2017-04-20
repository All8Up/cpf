# ###############################################
set (INCLUDE_FILES
	Include/Hash/Hash.hpp
	Include/Hash/HashID.hpp
	Include/Hash/HashString.hpp
	Include/Hash/Crc.hpp
	Include/Hash/Detail/Crc16Table.hpp
	Include/Hash/Detail/Crc32Table.hpp
	Include/Hash/Detail/Crc64Table.hpp
)

add_library (Hash INTERFACE)
target_link_libraries (Hash INTERFACE Configuration s_Collections)

target_include_directories (Hash INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
source_group (Interface FILES ${INCLUDE_FILES})

add_custom_target (Hash_IDE SOURCES ${INCLUDE_FILES})
set_property (TARGET Hash_IDE PROPERTY FOLDER Libraries/Interface/Platform)
source_group (Interface FILES ${INCLUDE_FILES})

install( DIRECTORY Include/Platform
	DESTINATION Include/Platform
	PATTERN *
)


install (TARGETS Hash
	EXPORT HashConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT HashConfig DESTINATION CMake)


# ###############################################
# ###############################################
MakeUnitTest (LIBRARY Hash GROUP Platform
	TEST_FILES
		UnitTest/Test_All.hpp
		UnitTest/Test_Crc.hpp
		UnitTest/Test_HashID.hpp
		UnitTest/Test_HashString.hpp
		../../Core/Test/UnitTestMain.cpp
)
