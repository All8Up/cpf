if (APPLE)

# ###############################################
set (INCLUDE_ADAPTERS_FILES
	Include/Adapters/Metal.hpp
)
set (SOURCE_ADAPTERS_FILES
	Source/Metal.cpp
)
set (INCLUDE_ADAPTERS_METAL_FILES
	Include/Adapters/Metal/MetalUtils.hpp
	Include/Adapters/Metal/Instance.hpp
	Include/Adapters/Metal/Adapter.hpp
	Include/Adapters/Metal/Device.hpp
	Include/Adapters/Metal/SwapChain.hpp
	Include/Adapters/Metal/CommandBuffer.hpp
	Include/Adapters/Metal/CommandPool.hpp
)
set (SOURCE_ADAPTERS_METAL_FILES
	Source/Metal/Instance.cpp
	Source/Metal/Adapter.cpp
	Source/Metal/Device.cpp
	Source/Metal/SwapChain.cpp
	Source/Metal/CommandBuffer.cpp
	Source/Metal/CommandPool.cpp
)


# ###############################################
add_library (s_AdapterMetal STATIC
	${INCLUDE_ADAPTERS_FILES}
	${SOURCE_ADAPTERS_FILES}
	${INCLUDE_ADAPTERS_METAL_FILES}
	${SOURCE_ADAPTERS_METAL_FILES}
)

# ###############################################
target_compile_definitions (s_AdapterMetal
	PUBLIC CPF_STATIC_ADAPTERS_METAL
	PRIVATE CPF_BUILD_ADAPTERS_METAL
)
target_include_directories (s_AdapterMetal
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_AdapterMetal
	LINK_PUBLIC
		Configuration s_RefCount s_Rtti s_Math s_IO s_Application s_GraphicsFactory s_GraphicsDriver Logging
)

# ###############################################
set_property (TARGET s_AdapterMetal
	PROPERTY FOLDER Libraries/Static/Adapters/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_ADAPTERS_FILES})
source_group (Headers\\Metal FILES ${INCLUDE_ADAPTERS_METAL_FILES})
source_group (Sources FILES ${SOURCE_ADAPTERS_FILES})
source_group (Sources\\Metal FILES ${SOURCE_ADAPTERS_METAL_FILES})

# ###############################################
install (TARGETS s_AdapterMetal
	EXPORT AdaptersMetalConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)


# ###############################################
install (EXPORT AdaptersMetalConfig DESTINATION CMake)

# APPLE
endif ()
