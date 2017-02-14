if (WIN32)

# ###############################################
set (INCLUDE_ADAPTERS_FILES
	Include/Adapters/D3D12.hpp
)
set (SOURCE_ADAPTERS_FILES
	Source/D3D12.cpp
)
set (INCLUDE_ADAPTERS_D3D12_FILES
	Include/Adapters/D3D12/d3dx12.h
	Include/Adapters/D3D12/Instance.hpp
	Include/Adapters/D3D12/Adapter.hpp
	Include/Adapters/D3D12/Device.hpp
	Include/Adapters/D3D12/SwapChain.hpp
	Include/Adapters/D3D12/CommandBuffer.hpp
	Include/Adapters/D3D12/CommandPool.hpp
	Include/Adapters/D3D12/Output.hpp
	Include/Adapters/D3D12/D3D12Utils.hpp
	Include/Adapters/D3D12/DescriptorManager.hpp
	Include/Adapters/D3D12/Image.hpp
	Include/Adapters/D3D12/Fence.hpp
	Include/Adapters/D3D12/Shader.hpp
	Include/Adapters/D3D12/Pipeline.hpp
	Include/Adapters/D3D12/ResourceBinding.hpp
	Include/Adapters/D3D12/Resource.hpp
	Include/Adapters/D3D12/IndexBuffer.hpp
	Include/Adapters/D3D12/VertexBuffer.hpp
	Include/Adapters/D3D12/ConstantBuffer.hpp
	Include/Adapters/D3D12/DescriptorPool.hpp
)
set (SOURCE_ADAPTERS_D3D12_FILES
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
	Source/D3D12/DescriptorPool.cpp
)


# ###############################################
add_library (s_AdaptersD3D12 STATIC
	${INCLUDE_ADAPTERS_FILES}
	${SOURCE_ADAPTERS_FILES}
	${INCLUDE_ADAPTERS_D3D12_FILES}
	${SOURCE_ADAPTERS_D3D12_FILES}
)

# ###############################################
target_compile_definitions (s_AdaptersD3D12
	PUBLIC CPF_STATIC_ADAPTERS_D3D12
	PRIVATE CPF_BUILD_ADAPTERS_D3D12
)
target_include_directories (s_AdaptersD3D12
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_AdaptersD3D12
	LINK_PUBLIC
		Configuration s_RefCount s_Math s_IO s_Application s_GraphicsFactory s_GraphicsDriver DXGI.lib d3d12.lib D3DCompiler.lib Logging
)

# ###############################################
set_property (TARGET s_AdaptersD3D12
	PROPERTY FOLDER Libraries/Static/Adapters/Graphics
)

# ###############################################
source_group (Headers FILES ${INCLUDE_ADAPTERS_FILES})
source_group (Headers\\D3D12 FILES ${INCLUDE_ADAPTERS_D3D12_FILES})
source_group (Sources FILES ${SOURCE_ADAPTERS_FILES})
source_group (Sources\\D3D12 FILES ${SOURCE_ADAPTERS_D3D12_FILES})

# ###############################################
install (TARGETS s_AdaptersD3D12
	EXPORT AdaptersD3D12Config
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)


# ###############################################
install (EXPORT AdaptersD3D12Config DESTINATION CMake)

# ###############################################
MakeUnitTest( LIBRARY s_AdaptersD3D12 GROUP Adapters
	TEST_FILES
		UnitTest/Test_All.hpp
		../../../UnitTesting/Source/Main.cpp
	LINK_LIBRARIES
		Configuration s_Simd s_Math
)

# WIN32
endif ()
