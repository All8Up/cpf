if (WIN32 OR UNIX AND NOT APPLE)

# ###############################################
set (INCLUDE_ADAPTERS_FILES
	Include/Adapter/Vulkan.hpp
)
set (SOURCE_ADAPTERS_FILES
	Source/Vulkan.cpp
)
set (INCLUDE_ADAPTERS_VULKAN_FILES
	Include/Adapter/Vulkan/VulkanUtils.hpp
	Include/Adapter/Vulkan/Instance.hpp
	Include/Adapter/Vulkan/Adapter.hpp
	Include/Adapter/Vulkan/Device.hpp
	Include/Adapter/Vulkan/SwapChain.hpp
	Include/Adapter/Vulkan/CommandBuffer.hpp
	Include/Adapter/Vulkan/CommandPool.hpp
)
set (SOURCE_ADAPTERS_VULKAN_FILES
	Source/Vulkan/Instance.cpp
	Source/Vulkan/Adapter.cpp
	Source/Vulkan/Device.cpp
	Source/Vulkan/SwapChain.cpp
	Source/Vulkan/CommandBuffer.cpp
	Source/Vulkan/CommandPool.cpp
)


# ###############################################
add_library (s_AdaptersVulkan STATIC
	${INCLUDE_ADAPTERS_FILES}
	${SOURCE_ADAPTERS_FILES}
	${INCLUDE_ADAPTERS_VULKAN_FILES}
	${SOURCE_ADAPTERS_VULKAN_FILES}
)

# ###############################################
target_compile_definitions (s_AdaptersVulkan
	PUBLIC CPF_STATIC_ADAPTERS_VULKAN
	PRIVATE CPF_BUILD_ADAPTERS_VULKAN
)
target_include_directories (s_AdaptersVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_AdaptersVulkan
	LINK_PUBLIC
		Configuration RefCount Math s_IO Logging GraphicsDriver_Interface vulkan
)

# ###############################################
set_property (TARGET s_AdaptersVulkan
	PROPERTY FOLDER Libraries/Static/Adapters/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_ADAPTERS_FILES})
source_group (Headers\\Vulkan FILES ${INCLUDE_ADAPTERS_VULKAN_FILES})
source_group (Sources FILES ${SOURCE_ADAPTERS_FILES})
source_group (Sources\\Vulkan FILES ${SOURCE_ADAPTERS_VULKAN_FILES})

# WIN32
endif ()
