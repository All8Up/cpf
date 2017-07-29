//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct RenderPassBeginDesc;
		struct iInstance;
		struct iCommandPool;
		struct iConstantBuffer;
		struct iResource;
		struct iIndexBuffer;
		struct iVertexBuffer;
		struct iFence;
		struct iImage;
		struct iImageView;
		struct iSwapChain;
		struct iShader;
		struct iSampler;
		struct iCommandBuffer;
		struct iResourceBinding;
		struct iPipeline;
		struct iRenderPass;
		struct iFrameBuffer;
		struct iBlob;

		struct WindowData;

		struct SamplerDesc;
		struct ClearValue;
		struct ResourceDesc;
		struct ImageDesc;
		struct DepthStencilViewDesc;
		struct SwapChainDesc;
		struct PipelineStateDesc;
		class ResourceBindingDesc;
		struct RenderPassDesc;
		struct FrameBufferDesc;

		enum class Format : int32_t;
		enum class HeapType : int32_t;
		enum class ShaderType : int32_t;
		enum class CommandBufferType : int32_t;

		struct iDevice : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iDevice"_crc64);

			virtual GOM::Result CPF_STDCALL Initialize() = 0;
			virtual GOM::Result CPF_STDCALL Shutdown() = 0;

			virtual GOM::Result CPF_STDCALL CreateSwapChain(iInstance*, const WindowData*, int32_t w, int32_t h, const SwapChainDesc*, iSwapChain**) = 0;
			virtual GOM::Result CPF_STDCALL CreateCommandPool(iCommandPool**) = 0;
			virtual GOM::Result CPF_STDCALL CreateCommandBuffer(iCommandPool*, CommandBufferType type, iCommandBuffer**) = 0;
			virtual GOM::Result CPF_STDCALL CreateFence(int64_t initValue, iFence**) = 0;
			virtual GOM::Result CPF_STDCALL CreateImage2D(HeapType heap, const ImageDesc* desc, const Graphics::ClearValue* clearValue, iImage**) = 0;
			virtual GOM::Result CPF_STDCALL CreateShader(iBlob* blob, iShader**) = 0;
			virtual GOM::Result CPF_STDCALL CreateResourceBinding(const ResourceBindingDesc*, iResourceBinding**) = 0;
			virtual GOM::Result CPF_STDCALL CreatePipeline(const PipelineStateDesc* desc, iResourceBinding*, iPipeline**) = 0;
			virtual GOM::Result CPF_STDCALL CreateResource(const ResourceDesc* desc, iResource**) = 0;
			virtual GOM::Result CPF_STDCALL CreateSampler(const SamplerDesc* desc, iSampler**) = 0;
			virtual GOM::Result CPF_STDCALL CreateRenderPass(const RenderPassDesc* desc, iRenderPass**) = 0;
			virtual GOM::Result CPF_STDCALL CreateFrameBuffer(const FrameBufferDesc* desc, iFrameBuffer** frameBuffer) = 0;

			virtual GOM::Result CPF_STDCALL CreateIndexBuffer(const ResourceDesc* desc, Format format, iIndexBuffer** indexBuffer) = 0;
			virtual GOM::Result CPF_STDCALL CreateVertexBuffer(const ResourceDesc* desc, int32_t stride, iVertexBuffer** indexBuffer) = 0;
			virtual GOM::Result CPF_STDCALL CreateConstantBuffer(const ResourceDesc*, const void* initData, iConstantBuffer**) = 0;

			virtual GOM::Result CPF_STDCALL CreateBlob(int64_t size, const void* data, iBlob**) = 0;

			virtual GOM::Result CPF_STDCALL CreateDepthStencilView(iImage*, const DepthStencilViewDesc*, iImageView**) = 0;

			virtual GOM::Result CPF_STDCALL Signal(iFence*, int64_t value) = 0;

			virtual void CPF_STDCALL Submit(int32_t count, iCommandBuffer**) = 0;

			// TODO: Probably temp.
			virtual GOM::Result CPF_STDCALL CompileToByteCode(const char* entryPoint, ShaderType type, size_t size, const char* source, iBlob**) = 0;
		};
	}
}
