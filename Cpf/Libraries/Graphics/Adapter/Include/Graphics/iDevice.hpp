//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Graphics/Driver.hpp"
#include "String.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		class iIndexBuffer;
		class iVertexBuffer;
		class iConstantBuffer;
		class iResource;
		struct iInstance;
		class iFence;
		class iImage;
		class iImageView;
		class iSwapChain;
		class iShader;
		class iSampler;
		class iCommandPool;
		class iCommandBuffer;
		class iResourceBinding;
		class iPipeline;
		struct iRenderPass;
		struct iFrameBuffer;

		class BinaryBlob;

		struct SamplerDesc;
		class ResourceDesc;
		struct ImageDesc;
		struct DepthStencilViewDesc;
		struct SwapChainDesc;
		struct PipelineStateDesc;
		class ResourceBindingDesc;
		struct RenderPassDesc;
		struct FrameBufferDesc;

		enum class Format : int32_t;
		enum class BufferUsage : int32_t;
		enum class ShaderType : int32_t;

		struct iDevice : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iDevice"_crc64);

			virtual bool CPF_STDCALL Initialize() = 0;
			virtual bool CPF_STDCALL Shutdown() = 0;

			virtual void CPF_STDCALL BeginFrame(iCommandBuffer*) = 0;
			virtual void CPF_STDCALL EndFrame(iCommandBuffer*) = 0;
			virtual void CPF_STDCALL Finalize() = 0;

			virtual bool CPF_STDCALL CreateSwapChain(iInstance*, iWindow*, const SwapChainDesc*, iSwapChain**) = 0;
			virtual bool CPF_STDCALL CreateCommandPool(iCommandPool**) = 0;
			virtual bool CPF_STDCALL CreateCommandBuffer(iCommandPool*, iCommandBuffer**) = 0;
			virtual bool CPF_STDCALL CreateFence(int64_t initValue, iFence**) = 0;
			virtual bool CPF_STDCALL CreateImage2D(const ImageDesc* desc, const void* initData, iImage**) = 0;
			virtual bool CPF_STDCALL CreateShader(BinaryBlob* blob, iShader**) = 0;
			virtual bool CPF_STDCALL CreateResourceBinding(const ResourceBindingDesc*, iResourceBinding**) = 0;
			virtual bool CPF_STDCALL CreatePipeline(const PipelineStateDesc* desc, iResourceBinding*, iPipeline**) = 0;
			virtual bool CPF_STDCALL CreateResource(const ResourceDesc* desc, iResource**) = 0;
			virtual bool CPF_STDCALL CreateSampler(const SamplerDesc* desc, iSampler**) = 0;
			virtual COM::Result CPF_STDCALL CreateRenderPass(const RenderPassDesc* desc, iRenderPass**) = 0;
			virtual COM::Result CPF_STDCALL CreateFrameBuffer(const FrameBufferDesc* desc, iFrameBuffer** frameBuffer) = 0;

			virtual bool CPF_STDCALL CreateIndexBuffer(Format format, BufferUsage usage, size_t byteSize, const void* initData, iIndexBuffer** indexBuffer) = 0;
			virtual bool CPF_STDCALL CreateVertexBuffer(BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, iVertexBuffer** indexBuffer) = 0;
			virtual bool CPF_STDCALL CreateConstantBuffer(size_t bufferSize, const void* initData, iConstantBuffer** CPF_GFX_DEBUG_PARAM_DECL) = 0;

			// TODO: Probably temp.
			virtual bool CPF_STDCALL CompileToByteCode(const String& entryPoint, ShaderType type, size_t size, char* source, BinaryBlob**) = 0;

			virtual bool CPF_STDCALL CreateDepthStencilView(iImage*, const DepthStencilViewDesc*, iImageView**) = 0;

			virtual bool CPF_STDCALL Signal(iFence*, int64_t value) = 0;

			virtual void CPF_STDCALL Submit(int32_t count, iCommandBuffer**) = 0;
		};
	}
}
