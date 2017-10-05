find_package(VULKAN)

if (WIN32 AND Vulkan_FOUND)

	set (INCLUDE_FILES
		Include/Vulkan.hpp
	)
	set (SOURCE_FILES
		Source/Vulkan.cpp
	)
	set (INCLUDE_VULKAN_FILES
		Include/Vulkan/Instance.hpp
	)
	set (SOURCE_VULKAN_FILES
		Source/Vulkan/Instance.cpp
	)

	# ###############################################
	add_library (AdapterVulkan SHARED
		${INCLUDE_FILES}
		${SOURCE_FILES}
		${INCLUDE_VULKAN_FILES}
		${SOURCE_VULKAN_FILES}
	)

	# ###############################################
	target_include_directories (AdapterVulkan
		PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
			$<INSTALL_INTERFACE:Include>
		PRIVATE
			${Vulkan_INCLUDE_DIR}
	)
	target_link_libraries (AdapterVulkan
		PUBLIC
			Configuration RefCount Math s_IO Logging GraphicsDriver ${Vulkan_LIBRARY}
	)

	# ###############################################
	set_property (TARGET AdapterVulkan
		PROPERTY FOLDER Plugins/Adapters/Graphics
	)

	# ###############################################
	source_group (Headers FILES ${INCLUDE_FILES})
	source_group (Sources FILES ${SOURCE_FILES})
	source_group (Headers\\Vulkan FILES ${INCLUDE_VULKAN_FILES})
	source_group (Sources\\Vulkan FILES ${SOURCE_VULKAN_FILES})

	# ###############################################
	# Copy as a plugin.
	add_custom_command (
		TARGET AdapterVulkan POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AdapterVulkan> ${CPF_COMMON_PLUGINS}/AdapterVulkan.cfp
	)

endif ()
