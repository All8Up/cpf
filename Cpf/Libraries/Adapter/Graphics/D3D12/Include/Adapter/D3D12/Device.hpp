//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IntrusivePtr.hpp"
#include "Adapter/D3D12.hpp"
#include "Adapter/D3D12/DescriptorManager.hpp"
#include "Graphics/Driver.hpp"
#include <d3d12.h>
#include "String.hpp"


namespace Cpf
{
	namespace Graphics
	{
		class iFence;
		class iAdapter;
		class iCommandPool;
		class iCommandBuffer;
		class iInstance;
		class iSwapChain;
		struct SwapChainDesc;
		struct PipelineStateDesc;
		class ResourceBindingDesc;
		class iResourceBinding;
		class iPipeline;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			class IndexBuffer;
			class VertexBuffer;

			CPF_EXPORT_ADAPTER_D3D12 class Device : public tRefCounted<Graphics::iDevice>
			{
			public:
				Device(Graphics::iAdapter* dev);
				virtual ~Device();

				bool Initialize() override;
				bool Shutdown() override;

				void BeginFrame(Graphics::iCommandBuffer*) override;
				void EndFrame(Graphics::iCommandBuffer*) override;
				void Finalize() override;

				bool CreateSwapChain(Graphics::iInstance*, iWindow*, const Graphics::SwapChainDesc*, Graphics::iSwapChain**) override;
				bool CreateCommandPool(Graphics::iCommandPool**) override;
				bool CreateCommandBuffer(Graphics::iCommandPool*, Graphics::iCommandBuffer**) override;
				bool CreateFence(int64_t initValue, Graphics::iFence**) override;
				bool CreateImage2D(const Graphics::ImageDesc* desc, Graphics::iImage**) override;
				bool CreateShader(Graphics::BinaryBlob* blob, Graphics::iShader**) override;
				bool CreateResourceBinding(const Graphics::ResourceBindingDesc*, Graphics::iResourceBinding**) override;
				bool CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding*, Graphics::iPipeline**) override;
				bool CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** resource) override;
				
				bool CreateIndexBuffer(Graphics::Format format, Graphics::BufferUsage usage, size_t byteSize, const void* initData, Graphics::iIndexBuffer** indexBuffer) override;
				bool CreateVertexBuffer(Graphics::BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, Graphics::iVertexBuffer** vertexBuffer) override;
				bool CreateConstantBuffer(size_t bufferSize, const void* initData, Graphics::iConstantBuffer**) override;

				bool CompileToByteCode(const String& entryPoint, Graphics::ShaderType type, size_t size, char* source, Graphics::BinaryBlob**) override;

				bool CreateDepthStencilView(Graphics::iImage*, const Graphics::DepthStencilViewDesc*, Graphics::iImageView**) override;

				bool Signal(Graphics::iFence*, int64_t value) override;
				void Submit(int32_t count, Graphics::iCommandBuffer**) override;

				//////////////////////////////////////////////////////////////////////////
				void QueueUpload(ID3D12Resource* src, ID3D12Resource* dst, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState);

				ID3D12Device* GetD3DDevice() const { return mpDevice; }
				ID3D12CommandQueue* GetD3DQueue() const { return mpQueue; }

				static constexpr size_t kConstantDescriptors = 1024;
				DescriptorManager& GetConstantDescriptors();
				static constexpr size_t kSamplerDescriptors = 64;
				DescriptorManager& GetSamplerDescriptors();
				static constexpr size_t kRenderTargetDescriptors = 1024;
				DescriptorManager& GetRenderTargetViewDescriptors();
				static constexpr size_t kDepthStencilDescriptors = 1024;
				DescriptorManager& GetDepthStencilViewDescriptors();

			private:
				IntrusivePtr<ID3D12Device> mpDevice;

				// TODO: Should probably be it's own class?
				IntrusivePtr<ID3D12CommandQueue> mpQueue;

				DescriptorManager mConstantDescriptors;
				DescriptorManager mSamplerDescriptors;
				DescriptorManager mRenderTargetDescriptors;
				DescriptorManager mDepthStencilDescriptors;

				enum class WorkType : int32_t
				{
					eUploadVertexBuffer
				};
				struct WorkEntry
				{
					WorkType mType;
					union
					{
						struct _UploadVertexBuffer
						{
							ID3D12Resource* mpSource;
							ID3D12Resource* mpDestination;
							D3D12_RESOURCE_STATES mDstStartState;
							D3D12_RESOURCE_STATES mDstEndState;
						} UploadVertexBuffer;
					};
				};

				Vector<WorkEntry> mUploadQueue;
				Vector<ID3D12Resource*> mReleaseQueue;
			};
		}
	}
}
