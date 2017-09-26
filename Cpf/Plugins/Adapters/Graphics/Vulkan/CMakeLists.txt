if (WIN32)

	set (INCLUDE_FILES
		Include/Vulkan.hpp
	)
	set (SOURCE_FILES
		Source/Vulkan.cpp
	)

	# ###############################################
	add_library (AdapterVulkan SHARED
		${INCLUDE_FILES}
		${SOURCE_FILES}
	)

	# ###############################################
	target_include_directories (AdapterVulkan
		PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
			$<INSTALL_INTERFACE:Include>
	)
	target_link_libraries (AdapterVulkan
		PUBLIC
			Configuration RefCount Math s_IO Logging GraphicsDriver
	)

	# ###############################################
	set_property (TARGET AdapterVulkan
		PROPERTY FOLDER Plugins/Adapters/Graphics
	)

	# ###############################################
	source_group (Headers FILES ${INCLUDE_FILES})
	source_group (Sources FILES ${SOURCE_FILES})

	# ###############################################
	# Copy as a plugin.
	add_custom_command (
		TARGET AdapterVulkan POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AdapterVulkan> ${CPF_COMMON_PLUGINS}/AdapterVulkan.cfp
	)

endif ()
