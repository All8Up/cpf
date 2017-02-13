#
set (INCLUDE_FILES
	Include/Std/Std.hpp
	Include/Std/CCType.hpp
	Include/Std/CwCType.hpp
	Include/Std/IO.hpp
	Include/Std/Memory.hpp
	Include/Std/String.hpp
	Include/Std/Time.hpp
)

set (SOURCE_FILES
	Source/Std.cpp
	Source/CCType.cpp
	Source/CwCType.cpp
	Source/IO.cpp
	Source/Memory.cpp
	Source/String.cpp
	Source/Time.cpp
)


add_library (s_Std STATIC ${INCLUDE_FILES} ${SOURCE_FILES})
add_library (Std SHARED ${INCLUDE_FILES} ${SOURCE_FILES})


target_compile_definitions (s_Std
	PUBLIC
		CPF_STATIC_STD
	PRIVATE
		CPF_BUILD_STD
)
target_compile_definitions (Std
	PRIVATE CPF_BUILD_STD
)


source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})


target_link_libraries (s_Std Configuration)
target_link_libraries (Std Configuration)


target_include_directories (s_Std PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
target_include_directories (Std PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)


set_property (TARGET s_Std PROPERTY FOLDER Libraries/Static/Core )
set_property (TARGET Std PROPERTY FOLDER Libraries/Shared/Core )


install (DIRECTORY Include/Std
	DESTINATION Include/Std
	PATTERN *
)


install (TARGETS s_Std
	EXPORT StdConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (TARGETS Std
	EXPORT StdConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT StdConfig DESTINATION CMake)


# ###############################################
MakeUnitTests( LIBRARY Std GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
