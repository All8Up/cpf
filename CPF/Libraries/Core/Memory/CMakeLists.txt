#
set (INCLUDE_FILES
	Include/Memory/Memory.hpp
)

set (SOURCE_FILES
	Source/Memory.cpp
)


add_library (s_Memory STATIC ${INCLUDE_FILES} ${SOURCE_FILES})


target_compile_definitions( s_Memory
	PUBLIC
		CPF_STATIC_MEMORY
	PRIVATE
		CPF_BUILD_MEMORY
)

source_group( Headers FILES ${INCLUDE_FILES} )
source_group( Sources FILES ${SOURCE_FILES} )


target_link_libraries( s_Memory CPF )


target_include_directories( s_Memory PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

set_property( TARGET s_Memory PROPERTY FOLDER Libraries/Static/Core )


install( DIRECTORY Include/Memory
	DESTINATION Include/Memory
	PATTERN *
)


install( TARGETS s_Memory
	EXPORT MemoryConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install( EXPORT MemoryConfig DESTINATION CMake )


# ###############################################
#[[
MakeUnitTests( LIBRARY Memory GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
]]#
