if (HAVE_D3D12 AND NOT CPF_PLUGIN_BINARY_PlatformGraphicsD3D12)
	if (WIN32)

	# ###############################################
	set (INCLUDE_ADAPTER_FILES
		Include/Driver/D3D12.hpp
	)
	set (SOURCE_ADAPTER_FILES
		Source/D3D12.cpp
	)
	set (INCLUDE_ADAPTER_D3D12_FILES
		Include/Driver/D3D12/d3dx12.h
		Include/Driver/D3D12/Instance.hpp
		Include/Driver/D3D12/Adapter.hpp
		Include/Driver/D3D12/Device.hpp
		Include/Driver/D3D12/SwapChain.hpp
		Include/Driver/D3D12/CommandBuffer.hpp
		Include/Driver/D3D12/Output.hpp
		Include/Driver/D3D12/D3D12Utils.hpp
		Include/Driver/D3D12/DescriptorManager.hpp
		Include/Driver/D3D12/Image.hpp
		Include/Driver/D3D12/ImageView.hpp
		Include/Driver/D3D12/Fence.hpp
		Include/Driver/D3D12/Shader.hpp
		Include/Driver/D3D12/Pipeline.hpp
		Include/Driver/D3D12/ResourceBinding.hpp
		Include/Driver/D3D12/Resource.hpp
		Include/Driver/D3D12/IndexBuffer.hpp
		Include/Driver/D3D12/VertexBuffer.hpp
		Include/Driver/D3D12/ConstantBuffer.hpp
		Include/Driver/D3D12/Sampler.hpp
		Include/Driver/D3D12/RenderPass.hpp
		Include/Driver/D3D12/FrameBuffer.hpp
		Include/Driver/D3D12/Plugin.hpp
		Include/Driver/D3D12/Blob.hpp
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
		Source/D3D12/ImageView.cpp
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
	add_library (PlatformGraphicsD3D12 SHARED
		${INCLUDE_ADAPTER_FILES}
		${SOURCE_ADAPTER_FILES}
		${INCLUDE_ADAPTER_D3D12_FILES}
		${SOURCE_ADAPTER_D3D12_FILES}
	)

	# ###############################################
	target_include_directories (PlatformGraphicsD3D12
		PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
			$<INSTALL_INTERFACE:Include>
	)
	target_link_libraries (PlatformGraphicsD3D12
		PUBLIC
			Core_s DXGI.lib d3d12.lib D3DCompiler.lib
	)

	# ###############################################
	set_property (TARGET PlatformGraphicsD3D12
		PROPERTY FOLDER Plugins/Drivers/Platform
	)

	# ###############################################
	if (CPF_BUILD_STATIC_VARIANTS)
		add_library (PlatformGraphicsD3D12_s STATIC
			${INCLUDE_ADAPTER_FILES}
			${SOURCE_ADAPTER_FILES}
			${INCLUDE_ADAPTER_D3D12_FILES}
			${SOURCE_ADAPTER_D3D12_FILES}
		)

		target_include_directories (PlatformGraphicsD3D12_s
			PUBLIC
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
				$<INSTALL_INTERFACE:Include>
		)
		target_link_libraries (PlatformGraphicsD3D12_s
			PUBLIC
				Core_s DXGI.lib d3d12.lib D3DCompiler.lib
		)
		target_compile_definitions (PlatformGraphicsD3D12_s
			PUBLIC
				PlatformGraphicsD3D12_STATIC=1
				CPF_PLUGIN_STATIC
		)

		# ###############################################
		set_property (TARGET PlatformGraphicsD3D12_s
			PROPERTY FOLDER Plugins/Drivers/Platform
		)
	endif ()

	# ###############################################
	source_group (Headers FILES ${INCLUDE_ADAPTER_FILES})
	source_group (Headers\\D3D12 FILES ${INCLUDE_ADAPTER_D3D12_FILES})
	source_group (Sources FILES ${SOURCE_ADAPTER_FILES})
	source_group (Sources\\D3D12 FILES ${SOURCE_ADAPTER_D3D12_FILES})

	# ###############################################
	# Copy as a plugin.
	add_custom_command (
		TARGET PlatformGraphicsD3D12 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlatformGraphicsD3D12> ${CPF_COMMON_PLUGINS}/PlatformGraphicsD3D12.cfp
	)

	# ###############################################
	cpf_binary_plugin(
		SHARED
		STATIC
		NAME
			PlatformGraphicsD3D12
		WIN32_LIBS
			DXGI d3d12 D3DCompiler
	)

	endif ()
endif ()
