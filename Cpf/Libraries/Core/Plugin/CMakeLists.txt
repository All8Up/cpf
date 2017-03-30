# ###############################################
set (INCLUDE_FILES
	Include/Plugin.hpp
)
set (INCLUDE_PLUGIN_FILES
	Include/Plugin/Factory.hpp
	Include/Plugin/Library.hpp
	Include/Plugin/Registry.hpp
)
set (INCLUDE_PLATFORM_FILES
	Include/${CPF_TARGET_OS}/Platform/SharedLibrary.hpp
)

add_library (Plugin INTERFACE)
target_link_libraries (Plugin INTERFACE Configuration RefCount)

target_include_directories (Plugin INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}>
	$<INSTALL_INTERFACE:Include/${CPF_TARGET_OS}>
)

add_custom_target (Plugin_IDE SOURCES ${INCLUDE_FILES} ${INCLUDE_PLUGIN_FILES} ${INCLUDE_PLATFORM_FILES})
set_property (TARGET Plugin_IDE PROPERTY FOLDER Libraries/Interface/Core)

source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Plugin FILES ${INCLUDE_PLUGIN_FILES})
source_group (Interface\\Platform FILES ${INCLUDE_PLATFORM_FILES})

install( DIRECTORY Include/Core
	DESTINATION Include/Core
	PATTERN *
)


install (TARGETS Plugin
	EXPORT PluginConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT PluginConfig DESTINATION CMake)

# ###############################################
add_library (TestPlugin SHARED
	UnitTest/TestPlugin/TestPlugin.hpp
	UnitTest/TestPlugin/TestPlugin.cpp
)
target_link_libraries (TestPlugin PUBLIC Plugin)
set_property (TARGET TestPlugin PROPERTY FOLDER UnitTests/Core/Plugins)

message ("${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message ("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set_target_properties (TestPlugin
	PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../Plugins"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../Plugins"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Plugins"
)

# ###############################################
if(MSVC)
	set (targetPath ${CMAKE_BINARY_DIR}/Cpf/Libraries/Core/Plugin)
else()
	set (targetPath /)
endif()
file (MAKE_DIRECTORY ${targetPath}/plugins)
add_custom_command (
	TARGET TestPlugin POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestPlugin> ${targetPath}/plugins/TestPlugin.cfp
)

MakeUnitTest (LIBRARY Plugin GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_IO
)
