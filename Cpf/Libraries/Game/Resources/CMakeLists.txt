# ###############################################
set (INCLUDE_FILES
	Include/Resources/Locator.hpp
	Include/Resources/Resource.hpp
	Include/Resources/Resources.hpp
	Include/Resources/ResourceConfig.hpp
)
set (CACHE_INCLUDE_FILES
	Include/Resources/Caches/Default.hpp
)
set (VOLUME_INCLUDE_FILES
	Include/Resources/Volumes/FileSystem.hpp
)
set (MONITOR_INCLUDE_FILES
	Include/Resources/Monitors/FileSystem.hpp
	Include/Resources/Monitors/Manual.hpp
)
set (INTERFACE_FILES
	Interface/Resources/ID.hpp
	Interface/Resources/iCache.hpp
	Interface/Resources/iConfiguration.hpp
	Interface/Resources/iLoader.hpp
	Interface/Resources/iLocator.hpp
	Interface/Resources/iMonitor.hpp
	Interface/Resources/iResource.hpp
	Interface/Resources/iVolume.hpp
)

set (SOURCE_FILES
	Source/Locator.cpp
	Source/Resource.cpp
	Source/Resources.cpp
	Source/ResourceConfig.cpp
	Source/Plugin.cpp
)
set (CACHE_SOURCE_FILES
	Source/Caches/Default.cpp
)
set (VOLUME_SOURCE_FILES
	Source/Volumes/FileSystem.cpp
)
set (MONITOR_SOURCE_FILES
	Source/Monitors/FileSystem.cpp
	Source/Monitors/Manual.cpp
)

add_library (Resources SHARED
	${INCLUDE_FILES}
	${CACHE_INCLUDE_FILES}
	${VOLUME_INCLUDE_FILES}
	${MONITOR_INCLUDE_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
	${CACHE_SOURCE_FILES}
	${VOLUME_SOURCE_FILES}
	${MONITOR_SOURCE_FILES}
)
target_include_directories (Resources
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)
target_compile_definitions (Resources PUBLIC CPF_STATIC_IO)
target_link_libraries (Resources
	LINK_PUBLIC
		Configuration
		s_Collections
		RefCount
		s_IO
		s_ANSI_C_FileSystem
		Logging
		GOM
		Plugin
		Events
		Hash
		jsoncons
		rapidjson
)
set_property (TARGET Resources PROPERTY FOLDER Plugins/Game)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Caches FILES ${CACHE_INCLUDE_FILES})
source_group (Headers\\Volumes FILES ${VOLUME_INCLUDE_FILES})
source_group (Headers\\Loaders FILES ${LOADER_INCLUDE_FILES})
source_group (Headers\\Monitors FILES ${MONITOR_INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Sources\\Caches FILES ${CACHE_SOURCE_FILES})
source_group (Sources\\Volumes FILES ${VOLUME_SOURCE_FILES})
source_group (Sources\\Loaders FILES ${LOADER_SOURCE_FILES})
source_group (Sources\\Monitors FILES ${MONITOR_SOURCE_FILES})


add_library (i_Resources INTERFACE)
target_include_directories (i_Resources
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
		$<INSTALL_INTERFACE:Interface>
)

add_custom_command (
	TARGET Resources POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Resources> ${CPF_COMMON_PLUGINS}/Resources.cfp
)
