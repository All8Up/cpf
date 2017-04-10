# ###############################################
set (INCLUDE_GRAPHICS_FILES
	Include/Graphics/Plugin.hpp
)
set (INCLUDE_GRAPHICS_FILES_INTERFACES
	Include/Graphics/iDebugUI.hpp
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
	Include/Graphics/BufferUsage.hpp
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

set (SOURCE_GRAPHICS_FILES
	Source/DebugUI.hpp
	Source/DebugUI.cpp
	Source/Graphics.cpp
	Source/PipelineStateDesc.cpp
	Source/Plugin.cpp
	Source/RasterizerStateDesc.cpp
)
set (SOURCE_IMGUI_FILES
	Source/imgui/imconfig.h
	Source/imgui/imgui.cpp
	Source/imgui/imgui.h
	Source/imgui/imgui_demo.cpp
	Source/imgui/imgui_draw.cpp
	Source/imgui/imgui_internal.h
	Source/imgui/stb_image.h
	Source/imgui/stb_image.cpp
	Source/imgui/stb_textedit.h
	Source/imgui/stb_truetype.h
	Source/imgui/stb_rect_pack.h
)

# ###############################################
add_library (s_GraphicsDriver STATIC
	Include/Graphics.hpp
	${INCLUDE_GRAPHICS_FILES}
	${INCLUDE_GRAPHICS_FILES_INTERFACES}
	${INCLUDE_GRAPHICS_FILES_DESCRIPTORS}
	${INCLUDE_GRAPHICS_FILES_STRUCTURES}
	${INCLUDE_GRAPHICS_FILES_FLAGS}
	${SOURCE_GRAPHICS_FILES}
	${SOURCE_IMGUI_FILES}
)

# ###############################################
target_compile_definitions (s_GraphicsDriver
	PUBLIC CPF_STATIC_GRAPHICS_DRIVER
	PRIVATE CPF_BUILD_GRAPHICS_DRIVER
)
target_include_directories (s_GraphicsDriver
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_GraphicsDriver
	LINK_PUBLIC
		Configuration RefCount Math s_Application s_SDL2 s_IO s_Resources Logging
)

# ###############################################
set_property (TARGET s_GraphicsDriver
	PROPERTY FOLDER Libraries/Static/Graphics
)

# ###############################################
source_group (Headers FILES Include/Graphics.hpp)
source_group (Headers\\Graphics FILES ${INCLUDE_GRAPHICS_FILES})
source_group (Headers\\Graphics\\Interfaces FILES ${INCLUDE_GRAPHICS_FILES_INTERFACES})
source_group (Headers\\Graphics\\Descriptors FILES ${INCLUDE_GRAPHICS_FILES_DESCRIPTORS})
source_group (Headers\\Graphics\\Structures FILES ${INCLUDE_GRAPHICS_FILES_STRUCTURES})
source_group (Headers\\Graphics\\Flags FILES ${INCLUDE_GRAPHICS_FILES_FLAGS})
source_group (Sources\\Graphics FILES ${SOURCE_GRAPHICS_FILES})
source_group (Sources\\Graphics\\imgui FILES ${SOURCE_IMGUI_FILES})

# ###############################################
add_library (GraphicsDriver_Interface INTERFACE)
target_include_directories (GraphicsDriver_Interface
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (GraphicsDriver_Interface INTERFACE Plugin)

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
