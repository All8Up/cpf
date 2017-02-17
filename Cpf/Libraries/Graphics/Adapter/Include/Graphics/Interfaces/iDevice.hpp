//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
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
		class iInstance;
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

		class iDevice : public iRefCounted
		{
		public:
			virtual ~iDevice() = 0;

			virtual bool Initialize() = 0;
			virtual bool Shutdown() = 0;

			virtual void BeginFrame(iCommandBuffer*) = 0;
			virtual void EndFrame(iCommandBuffer*) = 0;
			virtual void Finalize() = 0;

			virtual bool CreateSwapChain(iInstance*, iWindow*, const SwapChainDesc*, iSwapChain**) = 0;
			virtual bool CreateCommandPool(iCommandPool**) = 0;
			virtual bool CreateCommandBuffer(iCommandPool*, iCommandBuffer**) = 0;
			virtual bool CreateFence(int64_t initValue, iFence**) = 0;
			virtual bool CreateImage2D(const ImageDesc* desc, const void* initData, iImage**) = 0;
			virtual bool CreateShader(BinaryBlob* blob, iShader**) = 0;
			virtual bool CreateResourceBinding(const ResourceBindingDesc*, iResourceBinding**) = 0;
			virtual bool CreatePipeline(const PipelineStateDesc* desc, iResourceBinding*, iPipeline**) = 0;
			virtual bool CreateResource(const ResourceDesc* desc, iResource**) = 0;
			virtual bool CreateSampler(const SamplerDesc* desc, iSampler**) = 0;

			virtual bool CreateIndexBuffer(Format format, BufferUsage usage, size_t byteSize, const void* initData, iIndexBuffer** indexBuffer) = 0;
			virtual bool CreateVertexBuffer(BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, iVertexBuffer** indexBuffer) = 0;
			virtual bool CreateConstantBuffer(size_t bufferSize, const void* initData, iConstantBuffer**) = 0;

			// TODO: Probably temp.
			virtual bool CompileToByteCode(const String& entryPoint, ShaderType type, size_t size, char* source, BinaryBlob**) = 0;

			virtual bool CreateDepthStencilView(iImage*, const DepthStencilViewDesc*, iImageView**) = 0;

			virtual bool Signal(iFence*, int64_t value) = 0;

			virtual void Submit(int32_t count, iCommandBuffer**) = 0;
		};
	}
}
