if (NOT CPF_PLUGIN_BINARY_PlatformGraphicsVulkan)
	find_package(VULKAN)

	if (WIN32 AND Vulkan_FOUND)

		set (INCLUDE_FILES
			Include/Vulkan.hpp
		)
		set (SOURCE_FILES
			Source/Vulkan.cpp
		)
		set (INCLUDE_VULKAN_FILES
			Include/Vulkan/Adapter.hpp
			Include/Vulkan/CommandBuffer.hpp
			Include/Vulkan/CommandPool.hpp
			Include/Vulkan/Device.hpp
			Include/Vulkan/Fence.hpp
			Include/Vulkan/FrameBuffer.hpp
			Include/Vulkan/Image.hpp
			Include/Vulkan/ImageView.hpp
			Include/Vulkan/Instance.hpp
			Include/Vulkan/RenderPass.hpp
			Include/Vulkan/SwapChain.hpp
		)
		set (SOURCE_VULKAN_FILES
			Source/Vulkan/Adapter.cpp
			Source/Vulkan/CommandBuffer.cpp
			Source/Vulkan/CommandPool.cpp
			Source/Vulkan/Device.cpp
			Source/Vulkan/Fence.cpp
			Source/Vulkan/FrameBuffer.cpp
			Source/Vulkan/Image.cpp
			Source/Vulkan/ImageView.cpp
			Source/Vulkan/Instance.cpp
			Source/Vulkan/RenderPass.cpp
			Source/Vulkan/SwapChain.cpp
		)

		# ###############################################
		add_library (PlatformGraphicsVulkan SHARED
			${INCLUDE_FILES}
			${SOURCE_FILES}
			${INCLUDE_VULKAN_FILES}
			${SOURCE_VULKAN_FILES}
		)
		target_include_directories (PlatformGraphicsVulkan
			PUBLIC
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
				$<INSTALL_INTERFACE:Include>
			PRIVATE
				${Vulkan_INCLUDE_DIR}
		)
		target_link_libraries (PlatformGraphicsVulkan
			PUBLIC
				Core ${Vulkan_LIBRARY}
		)
		set_property (TARGET PlatformGraphicsVulkan
			PROPERTY FOLDER Plugins/Drivers/Platform
		)

		# ###############################################
		if (CPF_BUILD_STATIC_VARIANTS)
			add_library (PlatformGraphicsVulkan_s STATIC
				${INCLUDE_FILES}
				${SOURCE_FILES}
				${INCLUDE_VULKAN_FILES}
				${SOURCE_VULKAN_FILES}
			)
			target_include_directories (PlatformGraphicsVulkan_s
				PUBLIC
					$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
					$<INSTALL_INTERFACE:Include>
				PRIVATE
					${Vulkan_INCLUDE_DIR}
			)
			target_link_libraries (PlatformGraphicsVulkan_s
				PUBLIC
					Core_s ${Vulkan_LIBRARY}
			)
			target_compile_definitions (PlatformGraphicsVulkan_s
				PUBLIC
					PlatformVulkan_STATIC=1
					CPF_PLUGIN_STATIC
			)
			set_property (TARGET PlatformGraphicsVulkan_s
				PROPERTY FOLDER Plugins/Drivers/Platform
			)
		endif ()

		# ###############################################
		source_group (Headers FILES ${INCLUDE_FILES})
		source_group (Sources FILES ${SOURCE_FILES})
		source_group (Headers\\Vulkan FILES ${INCLUDE_VULKAN_FILES})
		source_group (Sources\\Vulkan FILES ${SOURCE_VULKAN_FILES})

		# ###############################################
		# Copy as a plugin.
		add_custom_command (
			TARGET PlatformGraphicsVulkan POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlatformGraphicsVulkan> ${CPF_COMMON_PLUGINS}/PlatformGraphicsVulkan.cfp
		)

		cpf_binary_plugin(
			SHARED
			STATIC
			NAME
				PlatformGraphicsVulkan
			WIN32_LIBS
				${Vulkan_LIBRARY}
		)
	endif ()
endif ()
