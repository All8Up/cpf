//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/Driver.hpp"
#include "String.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		struct SamplerDesc;
		enum class Format;
		enum class BufferUsage : int32_t;
		class iIndexBuffer;
		class iVertexBuffer;
		class iConstantBuffer;
		class iResource;
		class ResourceDesc;
		struct iInstance;
		class iFence;
		class iImage;
		class iImageView;
		class iSwapChain;
		struct ImageDesc;
		class iShader;
		class iSampler;
		class iCommandPool;
		class iCommandBuffer;
		class BinaryBlob;
		struct DepthStencilViewDesc;
		struct SwapChainDesc;
		enum class ShaderType;
		struct  PipelineStateDesc;
		class ResourceBindingDesc;
		class iResourceBinding;
		class iPipeline;
		struct RenderPassDesc;
		struct iRenderPass;
		struct iFrameBuffer;
		struct FrameBufferDesc;

		class iDevice : public iRefCounted
		{
		public:
			virtual ~iDevice() = 0;

			virtual bool Initialize() = 0;
			virtual bool Shutdown() = 0;

			virtual void BeginFrame(iCommandBuffer*) = 0;
			virtual void EndFrame(iCommandBuffer*) = 0;
			virtual void Finalize() = 0;

			virtual bool CreateSwapChain(iInstance*, iWindow*, const SwapChainDesc*, iSwapChain** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateCommandPool(iCommandPool** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateCommandBuffer(iCommandPool*, iCommandBuffer** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateFence(int64_t initValue, iFence** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateImage2D(const ImageDesc* desc, const void* initData, iImage** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateShader(BinaryBlob* blob, iShader**) = 0;
			virtual bool CreateResourceBinding(const ResourceBindingDesc*, iResourceBinding** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreatePipeline(const PipelineStateDesc* desc, iResourceBinding*, iPipeline** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateResource(const ResourceDesc* desc, iResource** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateSampler(const SamplerDesc* desc, iSampler** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual COM::Result CreateRenderPass(const RenderPassDesc* desc, iRenderPass** CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual COM::Result CreateFrameBuffer(const FrameBufferDesc* desc, iFrameBuffer** frameBuffer) = 0;

			virtual bool CreateIndexBuffer(Format format, BufferUsage usage, size_t byteSize, const void* initData, iIndexBuffer** indexBuffer CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateVertexBuffer(BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, iVertexBuffer** indexBuffer CPF_GFX_DEBUG_PARAM_DECL) = 0;
			virtual bool CreateConstantBuffer(size_t bufferSize, const void* initData, iConstantBuffer** CPF_GFX_DEBUG_PARAM_DECL) = 0;

			// TODO: Probably temp.
			virtual bool CompileToByteCode(const String& entryPoint, ShaderType type, size_t size, char* source, BinaryBlob**) = 0;

			virtual bool CreateDepthStencilView(iImage*, const DepthStencilViewDesc*, iImageView** CPF_GFX_DEBUG_PARAM_DECL) = 0;

			virtual bool Signal(iFence*, int64_t value) = 0;

			virtual void Submit(int32_t count, iCommandBuffer**) = 0;
		};
	}
}
