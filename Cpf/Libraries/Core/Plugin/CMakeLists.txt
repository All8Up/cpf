# ###############################################
set (IDL_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/iClassInstance.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/iRegistry.idl
)

# ###############################################
CPF_GEN_GOM(CppPluginFiles cpp
	hpp
	${CPF_GENERATED}/CPP/CPF/Plugin
	${IDL_FILES}
)
CPF_GEN_GOM(RustPluginFiles rust
	rs
	${CPF_GENERATED}/Rust/CPF/Plugin
	${IDL_FILES}
)

# ###############################################
set (INCLUDE_FILES
	Include/Plugin.hpp
)
set (INCLUDE_PLUGIN_FILES
	Include/Plugin/Library.hpp
	Include/Plugin/tClassInstance.hpp
)
set (INCLUDE_PLATFORM_FILES
	Include/${CPF_TARGET_OS}/Platform/SharedLibrary.hpp
)

add_custom_target (Plugin_IDE
	SOURCES
		${INCLUDE_FILES}
		${INCLUDE_PLUGIN_FILES}
		${INCLUDE_PLATFORM_FILES}
		${IDL_FILES}
		${CppPluginFiles}
		${RustPluginFiles}
)
set_property (TARGET Plugin_IDE PROPERTY FOLDER Libraries/Interface/Core)

source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Plugin FILES ${INCLUDE_PLUGIN_FILES} ${CppPluginFiles})
source_group (Interface\\Platform FILES ${INCLUDE_PLATFORM_FILES})
source_group (IDL FILES ${IDL_FILES})
source_group (Rust FILES ${RustPluginFiles})

add_library (Plugin INTERFACE)
add_dependencies (Plugin Plugin_IDE)
target_link_libraries (Plugin INTERFACE Configuration GOM)

target_include_directories (Plugin INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/${CPF_TARGET_OS}>
	$<INSTALL_INTERFACE:Include/${CPF_TARGET_OS}>
)

# ###############################################
if (CPF_ENABLE_UNITTESTS)
	add_library (TestPlugin SHARED
		UnitTest/TestPlugin/iTestPlugin.hpp
		UnitTest/TestPlugin/TestPlugin.cpp
	)
	target_link_libraries (TestPlugin PUBLIC Plugin)
	set_property (TARGET TestPlugin PROPERTY FOLDER UnitTests/Core/Plugins)

	set_target_properties (TestPlugin
		PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../Plugins"
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../Plugins"
			RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Plugins"
	)
endif ()

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
target_link_libraries (s_PluginHost PUBLIC Plugin s_IO Logging)
set_property (TARGET s_PluginHost PROPERTY FOLDER Libraries/Static/Core)
source_group ("Header Files" FILES ${PLUGINHOST_INCLUDE_FILES})
source_group ("Source Files" FILES ${PLUGINHOST_SOURCE_FILES})

#[[
install (TARGETS s_PluginHost
	EXPORT PluginHostConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT PluginHostConfig DESTINATION CMake)
]]#

# ###############################################
if (CPF_ENABLE_UNITTESTS)
	if(MSVC)
		set (targetPath ${CMAKE_BINARY_DIR}/Cpf/Libraries/Core/Plugin)
	else()
		set (targetPath test/)
	endif()
	file (MAKE_DIRECTORY ${targetPath}/plugins)
	# Copy to the normal location for running in the debugger.
	add_custom_command (
		TARGET TestPlugin POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestPlugin> ${targetPath}/plugins/TestPlugin.cfp
	)
	# Copy to the general purpose location for external tool testing.
	add_custom_command (
		TARGET TestPlugin POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TestPlugin> ${CPF_COMMON_PLUGINS}/TestPlugin.cfp
	)
endif ()

MakeUnitTest (LIBRARY Plugin GROUP Core
	TEST_FILES
		UnitTest/Test_All.hpp
		../Test/UnitTestMain.cpp
	LINK_LIBRARIES
		s_IO s_PluginHost
)
