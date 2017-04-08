//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IntrusivePtr.hpp"
#include "Adapter/D3D12.hpp"
#include "Adapter/D3D12/DescriptorManager.hpp"
#include "Graphics/Driver.hpp"
#include "Graphics/BinaryBlob.hpp"
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
		struct iInstance;
		class iSwapChain;
		struct SwapChainDesc;
		struct PipelineStateDesc;
		class ResourceBindingDesc;
		class iResourceBinding;
		class iPipeline;
		struct iFrameBuffer;
		struct FrameBufferDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			class IndexBuffer;
			class VertexBuffer;

			class CPF_EXPORT_ADAPTER_D3D12 Device : public tRefCounted<Graphics::iDevice>
			{
			public:
				Device(Graphics::iAdapter* dev);
				virtual ~Device();

				// Overrides from iUnknown.
				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				// Overrides from iDevice.
				bool CPF_STDCALL Initialize() override;
				bool CPF_STDCALL Shutdown() override;

				void CPF_STDCALL BeginFrame(Graphics::iCommandBuffer*) override;
				void CPF_STDCALL EndFrame(Graphics::iCommandBuffer*) override;
				void CPF_STDCALL Finalize() override;

				bool CPF_STDCALL CreateSwapChain(Graphics::iInstance*, iWindow*, const Graphics::SwapChainDesc*, Graphics::iSwapChain**) override;
				bool CPF_STDCALL CreateCommandPool(Graphics::iCommandPool**) override;
				bool CPF_STDCALL CreateCommandBuffer(Graphics::iCommandPool*, Graphics::iCommandBuffer**) override;
				bool CPF_STDCALL CreateFence(int64_t initValue, Graphics::iFence**) override;
				bool CPF_STDCALL CreateImage2D(const Graphics::ImageDesc* desc, const void* initData, Graphics::iImage**) override;
				bool CPF_STDCALL CreateShader(Graphics::BinaryBlob* blob, Graphics::iShader**) override;
				bool CPF_STDCALL CreateResourceBinding(const Graphics::ResourceBindingDesc*, Graphics::iResourceBinding**) override;
				bool CPF_STDCALL CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding*, Graphics::iPipeline**) override;
				bool CPF_STDCALL CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** resource) override;
				bool CPF_STDCALL CreateSampler(const Graphics::SamplerDesc* desc, Graphics::iSampler** sampler) override;
				COM::Result CPF_STDCALL CreateRenderPass(const Graphics::RenderPassDesc* desc, Graphics::iRenderPass** renderPass) override;
				COM::Result CPF_STDCALL CreateFrameBuffer(const Graphics::FrameBufferDesc* desc, Graphics::iFrameBuffer** frameBuffer) override;

				bool CPF_STDCALL CreateIndexBuffer(Graphics::Format format, Graphics::BufferUsage usage, size_t byteSize, const void* initData, Graphics::iIndexBuffer** indexBuffer) override;
				bool CPF_STDCALL CreateVertexBuffer(Graphics::BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, Graphics::iVertexBuffer** vertexBuffer) override;
				bool CPF_STDCALL CreateConstantBuffer(size_t bufferSize, const void* initData, Graphics::iConstantBuffer**) override;

				bool CPF_STDCALL CompileToByteCode(const String& entryPoint, Graphics::ShaderType type, size_t size, char* source, Graphics::BinaryBlob**) override;

				bool CPF_STDCALL CreateDepthStencilView(Graphics::iImage*, const Graphics::DepthStencilViewDesc*, Graphics::iImageView**) override;

				bool CPF_STDCALL Signal(Graphics::iFence*, int64_t value) override;
				void CPF_STDCALL Submit(int32_t count, Graphics::iCommandBuffer**) override;

				//////////////////////////////////////////////////////////////////////////
				void QueueUpload(ID3D12Resource* src, ID3D12Resource* dst, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState);
				void QueueUpdateSubResource(ID3D12Resource* src, ID3D12Resource* dst, D3D12_SUBRESOURCE_DATA& data, Graphics::BinaryBlob* blob, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState);

				ID3D12Device* GetD3DDevice() const { return mpDevice; }
				ID3D12CommandQueue* GetD3DQueue() const { return mpQueue; }

				static constexpr size_t kShaderResourceDescriptors = 1024;
				DescriptorManager& GetShaderResourceDescriptors();
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

				DescriptorManager mShaderResourceDescriptors;
				DescriptorManager mSamplerDescriptors;
				DescriptorManager mRenderTargetDescriptors;
				DescriptorManager mDepthStencilDescriptors;

				enum class WorkType : int32_t
				{
					eUploadVertexBuffer,
					eUpdateSubResource
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
						struct _UpdateSubResource
						{
							ID3D12Resource* mpSource;
							ID3D12Resource* mpDestination;
							Graphics::BinaryBlob* mpBlob;
							D3D12_SUBRESOURCE_DATA mData;
							D3D12_RESOURCE_STATES mDstStartState;
							D3D12_RESOURCE_STATES mDstEndState;
						} UpdateSubResource;
					};
				};

				Vector<WorkEntry> mUploadQueue;
				Vector<ID3D12Resource*> mReleaseQueue;
			};
		}
	}
}
