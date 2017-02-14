if (WIN32 OR UNIX AND NOT APPLE)

# ###############################################
set (INCLUDE_ADAPTERS_FILES
	Include/Adapters/Vulkan.hpp
)
set (SOURCE_ADAPTERS_FILES
	Source/Vulkan.cpp
)
set (INCLUDE_ADAPTERS_VULKAN_FILES
	Include/Adapters/Vulkan/VulkanUtils.hpp
	Include/Adapters/Vulkan/Instance.hpp
	Include/Adapters/Vulkan/Adapter.hpp
	Include/Adapters/Vulkan/Device.hpp
	Include/Adapters/Vulkan/SwapChain.hpp
	Include/Adapters/Vulkan/CommandBuffer.hpp
	Include/Adapters/Vulkan/CommandPool.hpp
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
		Configuration s_RefCount s_Math s_IO s_Application s_GraphicsFactory s_GraphicsDriver Logging vulkan
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

# ###############################################
install (TARGETS s_AdaptersVulkan
	EXPORT AdaptersVulkanConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)


# ###############################################
install (EXPORT AdaptersVulkanConfig DESTINATION CMake)

# WIN32
endif ()
