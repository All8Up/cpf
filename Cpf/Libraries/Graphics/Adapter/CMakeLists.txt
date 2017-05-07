# ###############################################
set (INCLUDE_GRAPHICS_FILES
	Include/Graphics/Plugin.hpp
)
set (INCLUDE_GRAPHICS_FILES_INTERFACES
	Include/Graphics/iDevice.hpp
	Include/Graphics/iAdapter.hpp
	Include/Graphics/iInstance.hpp
	Include/Graphics/iCommandBuffer.hpp
	Include/Graphics/iCommandPool.hpp
	Include/Graphics/iImage.hpp
	Include/Graphics/iImageView.hpp
	Include/Graphics/iSampler.hpp
	Include/Graphics/iSwapChain.hpp
	Include/Graphics/iOutput.hpp
	Include/Graphics/iFence.hpp
	Include/Graphics/iRenderPass.hpp
	Include/Graphics/iShader.hpp
	Include/Graphics/iPipeline.hpp
	Include/Graphics/iResourceBinding.hpp
	Include/Graphics/iResource.hpp
	Include/Graphics/iIndexBuffer.hpp
	Include/Graphics/iVertexBuffer.hpp
	Include/Graphics/iConstantBuffer.hpp
	Include/Graphics/iFrameBuffer.hpp
	Include/Graphics/iBlob.hpp
)
set (INCLUDE_GRAPHICS_FILES_DESCRIPTORS
	Include/Graphics/BlendStateDesc.hpp
	Include/Graphics/DepthStencilDesc.hpp
	Include/Graphics/InputLayoutDesc.hpp
	Include/Graphics/PipelineStateDesc.hpp
	Include/Graphics/RasterizerStateDesc.hpp
	Include/Graphics/SampleDesc.hpp
	Include/Graphics/ResourceBindingDesc.hpp
	Include/Graphics/ResourceDesc.hpp
	Include/Graphics/OutputDesc.hpp
	Include/Graphics/ModeDesc.hpp
	Include/Graphics/SamplerDesc.hpp
	Include/Graphics/SwapChainDesc.hpp
	Include/Graphics/AttachmentDesc.hpp
	Include/Graphics/SubPassDesc.hpp
	Include/Graphics/RenderPassDesc.hpp
	Include/Graphics/FrameBufferDesc.hpp
	Include/Graphics/RenderPassBeginDesc.hpp
	Include/Graphics/ImageDesc.hpp
	Include/Graphics/ImageViewDesc.hpp
	Include/Graphics/DepthStencilViewDesc.hpp
)
set (INCLUDE_GRAPHICS_FILES_STRUCTURES
	Include/Graphics/ResourceData.hpp
	Include/Graphics/Ratio.hpp
	Include/Graphics/Range.hpp
	Include/Graphics/Viewport.hpp
	Include/Graphics/ClearValue.hpp
	Include/Graphics/WindowData.hpp
)
set (INCLUDE_GRAPHICS_FILES_FLAGS
	Include/Graphics/BlendFunc.hpp
	Include/Graphics/BlendOp.hpp
	Include/Graphics/ComparisonFunc.hpp
	Include/Graphics/ConservativeRasterization.hpp
	Include/Graphics/CullMode.hpp
	Include/Graphics/DepthWriteMask.hpp
	Include/Graphics/Driver.hpp
	Include/Graphics/FillMode.hpp
	Include/Graphics/Format.hpp
	Include/Graphics/IndexStripCut.hpp
	Include/Graphics/LogicOp.hpp
	Include/Graphics/TopologyType.hpp
	Include/Graphics/StencilOp.hpp
	Include/Graphics/WindingOrder.hpp
	Include/Graphics/LoadOp.hpp
	Include/Graphics/StoreOp.hpp
	Include/Graphics/PipelineBindPoint.hpp
	Include/Graphics/DepthStencilClearFlag.hpp
	Include/Graphics/ResourceState.hpp
	Include/Graphics/SubResource.hpp
	Include/Graphics/WriteMask.hpp
	Include/Graphics/ImageFlags.hpp
	Include/Graphics/InputClassification.hpp
	Include/Graphics/ScanlineOrder.hpp
	Include/Graphics/ModeScaling.hpp
	Include/Graphics/ModeRotation.hpp
	Include/Graphics/EnumMode.hpp
	Include/Graphics/WrapMode.hpp
	Include/Graphics/FilterMode.hpp
	Include/Graphics/ShaderType.hpp
	Include/Graphics/SwapEffect.hpp
	Include/Graphics/BindingType.hpp
	Include/Graphics/ParamVisibility.hpp
	Include/Graphics/ParamFlags.hpp
	Include/Graphics/ResourceUsage.hpp
	Include/Graphics/ResourceType.hpp
	Include/Graphics/HeapType.hpp
	Include/Graphics/PrimitiveTopology.hpp
)

# ###############################################
add_library (GraphicsDriver INTERFACE)
target_include_directories (GraphicsDriver
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (GraphicsDriver INTERFACE Plugin Math)


# ###############################################
add_custom_target (GraphicsDriver_IDE
	SOURCES
		Include/Graphics.hpp
		${INCLUDE_GRAPHICS_FILES}
		${INCLUDE_GRAPHICS_FILES_INTERFACES}
		${INCLUDE_GRAPHICS_FILES_DESCRIPTORS}
		${INCLUDE_GRAPHICS_FILES_STRUCTURES}
		${INCLUDE_GRAPHICS_FILES_FLAGS}
)
set_property (TARGET GraphicsDriver_IDE PROPERTY FOLDER Libraries/Interface/Graphics)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Platform FILES ${PLATFORM_INCLUDE_FILES})

# ###############################################
source_group (Headers FILES Include/Graphics.hpp)
source_group (Headers\\Graphics FILES ${INCLUDE_GRAPHICS_FILES})
source_group (Headers\\Graphics\\Interfaces FILES ${INCLUDE_GRAPHICS_FILES_INTERFACES})
source_group (Headers\\Graphics\\Descriptors FILES ${INCLUDE_GRAPHICS_FILES_DESCRIPTORS})
source_group (Headers\\Graphics\\Structures FILES ${INCLUDE_GRAPHICS_FILES_STRUCTURES})
source_group (Headers\\Graphics\\Flags FILES ${INCLUDE_GRAPHICS_FILES_FLAGS})

# ###############################################
#[[
install (TARGETS s_GraphicsDriver
	EXPORT GraphicsDriverConfig
	CONFIGURATIONS Debug Release
	ARCHIVE DESTINATION ${CPF_STATIC_LIB_DIR}
	LIBRARY DESTINATION ${CPF_SHARED_LIB_DIR}
)

# ###############################################
install (EXPORT GraphicsDriverConfig DESTINATION CMake)
#]]
