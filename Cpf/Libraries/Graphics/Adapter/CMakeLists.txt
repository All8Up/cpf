# ###############################################
set (IDL_INTERFACES
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iAdapter.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iBlob.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iCommandPool.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iCommandBuffer.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iConstantBuffer.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iDevice.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iFence.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iFrameBuffer.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iImage.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iImageView.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iIndexBuffer.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iInstance.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iOutput.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iPipeline.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iRenderPass.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iResource.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iResourceBinding.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iSampler.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iShader.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iSwapChain.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Interfaces/iVertexBuffer.idl
)

# ###############################################
CPF_GEN_GOM(CPP_GRAPHICS_INTERFACES cpp
	hpp
	${CPF_GENERATED}/CPP/Graphics
	${IDL_INTERFACES}
)
CPF_GEN_GOM(RUST_GRAPHICS_INTERFACES rust
	rs
	${CPF_GENERATED}/Rust/Graphics
	${IDL_INTERFACES}
)

# ###############################################
set (IDL_STRUCTURES
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/ClearValue.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/Range.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/Ratio.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/ResourceData.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/Viewport.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/WindowData.idl
)
CPF_GEN_GOM(CPP_GRAPHICS_STRUCTURES cpp
	hpp
	${CPF_GENERATED}/CPP/Graphics
	${IDL_STRUCTURES}
)
CPF_GEN_GOM(RUST_GRAPHICS_STRUCTURES rust
	rs
	${CPF_GENERATED}/Rust/Graphics
	${IDL_STRUCTURES}
)

# ###############################################
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
	${CPP_GRAPHICS_STRUCTURES}
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
		${CPP_GRAPHICS_INTERFACES}
		${INCLUDE_GRAPHICS_FILES_DESCRIPTORS}
		${INCLUDE_GRAPHICS_FILES_STRUCTURES}
		${INCLUDE_GRAPHICS_FILES_FLAGS}
		${IDL_INTERFACES}
		${IDL_STRUCTURES}
)
set_property (TARGET GraphicsDriver_IDE PROPERTY FOLDER Libraries/Interface/Graphics)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Platform FILES ${PLATFORM_INCLUDE_FILES})

add_dependencies (GraphicsDriver GraphicsDriver_IDE)


# ###############################################
source_group (IDL\\Interfaces FILES ${IDL_INTERFACES})
source_group (IDL\\Structures FILES ${IDL_STRUCTURES})
source_group (Headers FILES Include/Graphics.hpp)
source_group (Headers\\Graphics FILES ${INCLUDE_GRAPHICS_FILES})
source_group (Headers\\Graphics\\Interfaces FILES ${CPP_GRAPHICS_INTERFACES})
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
