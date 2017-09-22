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
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Structures/SampleDesc.idl
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
set (IDL_DESCRIPTORS
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/AttachmentDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/BlendStateDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/DepthStencilStateDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/DependencyDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/DepthStencilViewDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/FrameBufferDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/ImageDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/ImageViewDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/InputElementDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/ModeDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/OutputDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/RasterizerStateDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/RenderPassBeginDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/RenderPassDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/RenderTargetBlendStateDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/ResourceDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/SamplerDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/SubPassDesc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Descriptors/SwapChainDesc.idl
)
CPF_GEN_GOM(CPP_GRAPHICS_DESCRIPTORS cpp
	hpp
	${CPF_GENERATED}/CPP/Graphics
	${IDL_DESCRIPTORS}
)
CPF_GEN_GOM(RUST_GRAPHICS_DESCRIPTORS rust
	rs
	${CPF_GENERATED}/Rust/Graphics
	${IDL_DESCRIPTORS}
)

# ###############################################
set (IDL_FLAGS
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/BindingType.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/BlendFunc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/BlendOp.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ComparisonFunc.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ConservativeRasterization.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/CullMode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/DepthStencilClearFlag.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/DepthWriteMask.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/EnumMode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/FillMode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/FilterMode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/Format.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/HeapType.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ImageFlags.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/IndexStripCut.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/InputClassification.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/LoadOp.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/LogicOp.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ModeRotation.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ModeScaling.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ParamFlags.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ParamVisibility.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/PipelineBindPoint.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/PrimitiveTopology.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ResourceState.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ResourceType.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ResourceUsage.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ScanlineOrder.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/ShaderType.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/StencilOp.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/StoreOp.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/SubResource.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/SwapEffect.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/TopologyType.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/WindingOrder.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/WrapMode.idl
	${CMAKE_CURRENT_SOURCE_DIR}/IDL/Flags/WriteMask.idl
)
CPF_GEN_GOM(CPP_GRAPHICS_FLAGS cpp
	hpp
	${CPF_GENERATED}/CPP/Graphics
	${IDL_FLAGS}
)
CPF_GEN_GOM(RUST_GRAPHICS_FLAGS rust
	rs
	${CPF_GENERATED}/Rust/Graphics
	${IDL_FLAGS}
)

# ###############################################
set (RUST_FILES ${RUST_GRAPHICS_INTERFACES} ${RUST_GRAPHICS_STRUCTURES} ${RUST_GRAPHICS_DESCRIPTORS} ${RUST_GRAPHICS_FLAGS})
source_group (Rust\\Interfaces FILES ${RUST_GRAPHICS_INTERFACES})
source_group (Rust\\Structures FILES ${RUST_GRAPHICS_STRUCTURES})
source_group (Rust\\Descriptors FILES ${RUST_GRAPHICS_DESCRIPTORS})
source_group (Rust\\Flags FILES ${RUST_GRAPHICS_FLAGS})

# ###############################################
set (INCLUDE_GRAPHICS_FILES_DESCRIPTORS
	${CPP_GRAPHICS_DESCRIPTORS}
	Include/Graphics/BlendStateBuilder.hpp
	Include/Graphics/DepthStencilBuilder.hpp
	Include/Graphics/PipelineStateBuilder.hpp
	Include/Graphics/RasterizerStateBuilder.hpp
	Include/Graphics/InputLayoutDesc.hpp
	Include/Graphics/PipelineStateDesc.hpp
	Include/Graphics/ResourceBindingDesc.hpp
)
set (INCLUDE_GRAPHICS_FILES_STRUCTURES
	${CPP_GRAPHICS_STRUCTURES}
)
set (INCLUDE_GRAPHICS_FILES_FLAGS
	${CPP_GRAPHICS_FLAGS}
	Include/Graphics/FormatSize.hpp
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
		${CPP_GRAPHICS_INTERFACES}
		${INCLUDE_GRAPHICS_FILES_DESCRIPTORS}
		${INCLUDE_GRAPHICS_FILES_STRUCTURES}
		${INCLUDE_GRAPHICS_FILES_FLAGS}
		${IDL_INTERFACES}
		${IDL_STRUCTURES}
		${IDL_DESCRIPTORS}
		${IDL_FLAGS}
		${RUST_FILES}
)
set_property (TARGET GraphicsDriver_IDE PROPERTY FOLDER Libraries/Interface/Graphics)
source_group (Interface FILES ${INCLUDE_FILES})
source_group (Interface\\Platform FILES ${PLATFORM_INCLUDE_FILES})

add_dependencies (GraphicsDriver GraphicsDriver_IDE)


# ###############################################
source_group (IDL\\Interfaces FILES ${IDL_INTERFACES})
source_group (IDL\\Structures FILES ${IDL_STRUCTURES})
source_group (IDL\\Descriptors FILES ${IDL_DESCRIPTORS})
source_group (IDL\\Flags FILES ${IDL_FLAGS})
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
