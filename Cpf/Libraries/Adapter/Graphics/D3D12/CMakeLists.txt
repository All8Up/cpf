if (WIN32)

# ###############################################
set (INCLUDE_ADAPTER_FILES
	Include/Adapter/D3D12.hpp
)
set (SOURCE_ADAPTER_FILES
	Source/D3D12.cpp
)
set (INCLUDE_ADAPTER_D3D12_FILES
	Include/Adapter/D3D12/d3dx12.h
	Include/Adapter/D3D12/Instance.hpp
	Include/Adapter/D3D12/Adapter.hpp
	Include/Adapter/D3D12/Device.hpp
	Include/Adapter/D3D12/SwapChain.hpp
	Include/Adapter/D3D12/CommandBuffer.hpp
	Include/Adapter/D3D12/Output.hpp
	Include/Adapter/D3D12/D3D12Utils.hpp
	Include/Adapter/D3D12/DescriptorManager.hpp
	Include/Adapter/D3D12/Image.hpp
	Include/Adapter/D3D12/Fence.hpp
	Include/Adapter/D3D12/Shader.hpp
	Include/Adapter/D3D12/Pipeline.hpp
	Include/Adapter/D3D12/ResourceBinding.hpp
	Include/Adapter/D3D12/Resource.hpp
	Include/Adapter/D3D12/IndexBuffer.hpp
	Include/Adapter/D3D12/VertexBuffer.hpp
	Include/Adapter/D3D12/ConstantBuffer.hpp
	Include/Adapter/D3D12/Sampler.hpp
	Include/Adapter/D3D12/RenderPass.hpp
	Include/Adapter/D3D12/FrameBuffer.hpp
	Include/Adapter/D3D12/Plugin.hpp
	Include/Adapter/D3D12/Blob.hpp
)
set (SOURCE_ADAPTER_D3D12_FILES
	Source/D3D12/Instance.cpp
	Source/D3D12/Adapter.cpp
	Source/D3D12/Device.cpp
	Source/D3D12/SwapChain.cpp
	Source/D3D12/CommandBuffer.cpp
	Source/D3D12/CommandPool.cpp
	Source/D3D12/Output.cpp
	Source/D3D12/D3D12Utils.cpp
	Source/D3D12/DescriptorManager.cpp
	Source/D3D12/Image.cpp
	Source/D3D12/Fence.cpp
	Source/D3D12/Shader.cpp
	Source/D3D12/Pipeline.cpp
	Source/D3D12/ResourceBinding.cpp
	Source/D3D12/Resource.cpp
	Source/D3D12/IndexBuffer.cpp
	Source/D3D12/VertexBuffer.cpp
	Source/D3D12/ConstantBuffer.cpp
	Source/D3D12/Sampler.cpp
	Source/D3D12/RenderPass.cpp
	Source/D3D12/FrameBuffer.cpp
	Source/D3D12/Plugin.cpp
	Source/D3D12/Blob.cpp
)


# ###############################################
add_library (AdapterD3D12 SHARED
	${INCLUDE_ADAPTER_FILES}
	${SOURCE_ADAPTER_FILES}
	${INCLUDE_ADAPTER_D3D12_FILES}
	${SOURCE_ADAPTER_D3D12_FILES}
)

# ###############################################
target_include_directories (AdapterD3D12
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (AdapterD3D12
	PUBLIC
		Configuration RefCount Math s_IO Logging GraphicsDriver_Interface DXGI.lib d3d12.lib D3DCompiler.lib
)

# ###############################################
set_property (TARGET AdapterD3D12
	PROPERTY FOLDER Plugins/Adapter/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_ADAPTER_FILES})
source_group (Headers\\D3D12 FILES ${INCLUDE_ADAPTER_D3D12_FILES})
source_group (Sources FILES ${SOURCE_ADAPTER_FILES})
source_group (Sources\\D3D12 FILES ${SOURCE_ADAPTER_D3D12_FILES})

# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET AdapterD3D12 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AdapterD3D12> ${CPF_COMMON_PLUGINS}/AdapterD3D12.cfp
)

# ###############################################
#[[
install (TARGETS AdapterD3D12
	EXPORT AdapterD3D12Config
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)


# ###############################################
install (EXPORT AdapterD3D12Config DESTINATION CMake)

# ###############################################
MakeUnitTest( LIBRARY AdapterD3D12 GROUP Adapter
	TEST_FILES
		UnitTest/Test_All.hpp
		../../../Core/Test/UnitTestMain.cpp
	LINK_LIBRARIES
		Configuration Math
)

# WIN32
#]]
endif ()
