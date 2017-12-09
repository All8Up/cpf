#
set (INCLUDE_FILES
	Include/Std/Std.hpp
	Include/Std/CCType.hpp
	Include/Std/CwCType.hpp
	Include/Std/IO.hpp
	Include/Std/Memory.hpp
	Include/Std/String.hpp
	Include/Std/Time.hpp
	Include/Std/Common.hpp
	Include/Std/Hash.hpp
)

add_library (Std INTERFACE)
target_link_libraries (Std INTERFACE Configuration)
target_include_directories (Std INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)

add_custom_target (Std_IDE SOURCES ${INCLUDE_FILES} ${PLATFORM_INCLUDE_FILES})
set_property (TARGET Std_IDE PROPERTY FOLDER Libraries/Interface/Core)
source_group (Interface FILES ${INCLUDE_FILES})


install (DIRECTORY Include/Std
	DESTINATION Include/Std
	PATTERN *
)

install (TARGETS Std
	EXPORT StdConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT StdConfig DESTINATION CMake)


# ###############################################
#[[
MakeUnitTests( LIBRARY Std GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
)
]]#
