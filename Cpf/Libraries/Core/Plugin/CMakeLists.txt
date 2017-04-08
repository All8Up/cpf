# ###############################################
set (INCLUDE_FILES
	Include/Plugin.hpp
)
set (INCLUDE_PLUGIN_FILES
	Include/Plugin/Library.hpp
	Include/Plugin/iRegistry.hpp
	Include/Plugin/iClassInstance.hpp
	Include/Plugin/Context.hpp
)
set (INCLUDE_PLATFORM_FILES
	Include/${CPF_TARGET_OS}/Platform/SharedLibrary.hpp
)

add_library (Plugin INTERFACE)
target_link_libraries (Plugin INTERFACE Configuration COM)

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
	UnitTest/TestPlugin/iTestPlugin.hpp
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
set (PLUGINHOST_INCLUDE_FILES
	Include/PluginHost/Registry.hpp
)
set (PLUGINHOST_SOURCE_FILES
	Source/Registry.cpp
)
add_library (s_PluginHost STATIC
	${PLUGINHOST_INCLUDE_FILES}
	${PLUGINHOST_SOURCE_FILES}
)
target_link_libraries (s_PluginHost PUBLIC Plugin)
set_property (TARGET s_PluginHost PROPERTY FOLDER Libraries/Static/Core)
source_group ("Header Files" FILES ${PLUGINHOST_INCLUDE_FILES})
source_group ("Source Files" FILES ${PLUGINHOST_SOURCE_FILES})

install (TARGETS s_PluginHost
	EXPORT PluginHostConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT PluginHostConfig DESTINATION CMake)

# ###############################################
if(MSVC)
	set (targetPath ${CMAKE_BINARY_DIR}/Cpf/Libraries/Core/Plugin)
else()
	set (targetPath test/)
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
		s_IO s_PluginHost
)
