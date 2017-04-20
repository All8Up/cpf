# ###############################################
set (INCLUDE_FILES
	Include/Resources/Cache.hpp
	Include/Resources/ID.hpp
	Include/Resources/Loader.hpp
	Include/Resources/Locator.hpp
	Include/Resources/Monitor.hpp
	Include/Resources/Resource.hpp
	Include/Resources/Resources.hpp
	Include/Resources/Volume.hpp
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

set (SOURCE_FILES
	Source/Cache.cpp
	Source/Loader.cpp
	Source/Locator.cpp
	Source/Monitor.cpp
	Source/Resource.cpp
	Source/Resources.cpp
	Source/Volume.cpp
	Source/ResourceConfig.cpp
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

add_library (s_Resources STATIC
	${INCLUDE_FILES}
	${CACHE_INCLUDE_FILES}
	${VOLUME_INCLUDE_FILES}
	${MONITOR_INCLUDE_FILES}
	${SOURCE_FILES}
	${CACHE_SOURCE_FILES}
	${VOLUME_SOURCE_FILES}
	${MONITOR_SOURCE_FILES}
)
target_compile_definitions (s_Resources
	PUBLIC CPF_STATIC_RESOURCES
	PRIVATE CPF_BUILD_RESOURCES
)
target_include_directories (s_Resources
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_Resources
	LINK_PUBLIC
		Configuration s_Collections RefCount s_IO Logging Events Hash rapidjson
)
set_property (TARGET s_Resources PROPERTY FOLDER Libraries/Static/Game)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Headers\\Caches FILES ${CACHE_INCLUDE_FILES})
source_group (Headers\\Volumes FILES ${VOLUME_INCLUDE_FILES})
source_group (Headers\\Loaders FILES ${LOADER_INCLUDE_FILES})
source_group (Headers\\Monitors FILES ${MONITOR_INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Sources\\Caches FILES ${CACHE_SOURCE_FILES})
source_group (Sources\\Volumes FILES ${VOLUME_SOURCE_FILES})
source_group (Sources\\Loaders FILES ${LOADER_SOURCE_FILES})
source_group (Sources\\Monitors FILES ${MONITOR_SOURCE_FILES})

# ###############################################
#[[
install (TARGETS s_Resources
	EXPORT ResourcesSystemConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)
install (EXPORT ResourcesSystemConfig DESTINATION CMake)
]]#
