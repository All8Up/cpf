//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IntrusivePtr.hpp"
#include "Adapter/D3D12/DescriptorManager.hpp"
#include "Graphics/Driver.hpp"
#include "Graphics/iBlob.hpp"
#include <d3d12.h>
#include "Plugin/iClassInstance.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iInstance;
		struct iAdapter;
		struct iCommandPool;
		struct iCommandBuffer;
		struct iFence;
		struct iSwapChain;
		struct iResourceBinding;
		struct iPipeline;
		struct iFrameBuffer;

		struct SwapChainDesc;
		struct PipelineStateDesc;
		class ResourceBindingDesc;
		struct RenderPassDesc;
		struct FrameBufferDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			class IndexBuffer;
			class VertexBuffer;

			static constexpr COM::ClassID kDeviceCID = COM::ClassID("Adapter::D3D12::Device"_crc64);

			class Device : public tRefCounted<Graphics::iDevice>
			{
			public:
				// Internal.
				COM::Result Initialize(Graphics::iAdapter* adapter);

				// Overrides from iUnknown.
				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				// Overrides from iDevice.
				COM::Result CPF_STDCALL Initialize() override;
				COM::Result CPF_STDCALL Shutdown() override;

				void CPF_STDCALL BeginFrame(Graphics::iCommandBuffer*) override;
				void CPF_STDCALL Finalize() override;

				COM::Result CPF_STDCALL CreateSwapChain(Graphics::iInstance*, const Graphics::WindowData*, int32_t w, int32_t h, const Graphics::SwapChainDesc*, Graphics::iSwapChain**) override;
				COM::Result CPF_STDCALL CreateCommandPool(Graphics::iCommandPool**) override;
				COM::Result CPF_STDCALL CreateCommandBuffer(Graphics::iCommandPool*, Graphics::CommandBufferType type, Graphics::iCommandBuffer**) override;
				COM::Result CPF_STDCALL CreateFence(int64_t initValue, Graphics::iFence**) override;
				COM::Result CPF_STDCALL CreateImage2D(Graphics::HeapType heap, const Graphics::ImageDesc* desc, const void* initData, Graphics::iImage**) override;
				COM::Result CPF_STDCALL CreateShader(Graphics::iBlob* blob, Graphics::iShader**) override;
				COM::Result CPF_STDCALL CreateResourceBinding(const Graphics::ResourceBindingDesc*, Graphics::iResourceBinding**) override;
				COM::Result CPF_STDCALL CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding*, Graphics::iPipeline**) override;
				COM::Result CPF_STDCALL CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** resource) override;
				COM::Result CPF_STDCALL CreateSampler(const Graphics::SamplerDesc* desc, Graphics::iSampler** sampler) override;
				COM::Result CPF_STDCALL CreateRenderPass(const Graphics::RenderPassDesc* desc, Graphics::iRenderPass** renderPass) override;
				COM::Result CPF_STDCALL CreateFrameBuffer(const Graphics::FrameBufferDesc* desc, Graphics::iFrameBuffer** frameBuffer) override;

				COM::Result CPF_STDCALL CreateIndexBuffer(Graphics::Format format, Graphics::BufferUsage usage, size_t byteSize, const void* initData, Graphics::iIndexBuffer** indexBuffer) override;
				COM::Result CPF_STDCALL CreateVertexBuffer(Graphics::BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData, Graphics::iVertexBuffer** vertexBuffer) override;
				COM::Result CPF_STDCALL CreateConstantBuffer(size_t bufferSize, const void* initData, Graphics::iConstantBuffer**) override;

				COM::Result CPF_STDCALL CreateBlob(int64_t size, const void* data, Graphics::iBlob**) override;

				COM::Result CPF_STDCALL CompileToByteCode(const char* entryPoint, Graphics::ShaderType type, size_t size, const char* source, Graphics::iBlob**) override;

				COM::Result CPF_STDCALL CreateDepthStencilView(Graphics::iImage*, const Graphics::DepthStencilViewDesc*, Graphics::iImageView**) override;

				COM::Result CPF_STDCALL Signal(Graphics::iFence*, int64_t value) override;
				void CPF_STDCALL Submit(int32_t count, Graphics::iCommandBuffer**) override;

				//////////////////////////////////////////////////////////////////////////
				// Internal
				void CPF_STDCALL QueueUpload(ID3D12Resource* src, ID3D12Resource* dst, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState);
				void CPF_STDCALL QueueUpdateSubResource(ID3D12Resource* src, ID3D12Resource* dst, D3D12_SUBRESOURCE_DATA& data, Graphics::iBlob* blob, D3D12_RESOURCE_STATES dstStartState, D3D12_RESOURCE_STATES dstEndState);

				ID3D12Device* CPF_STDCALL GetD3DDevice() const { return mpDevice; }
				ID3D12CommandQueue* CPF_STDCALL GetD3DQueue() const { return mpQueue; }

				static constexpr size_t kShaderResourceDescriptors = 1024;
				DescriptorManager& CPF_STDCALL GetShaderResourceDescriptors();
				static constexpr size_t kSamplerDescriptors = 64;
				DescriptorManager& CPF_STDCALL GetSamplerDescriptors();
				static constexpr size_t kRenderTargetDescriptors = 1024;
				DescriptorManager& CPF_STDCALL GetRenderTargetViewDescriptors();
				static constexpr size_t kDepthStencilDescriptors = 1024;
				DescriptorManager& CPF_STDCALL GetDepthStencilViewDescriptors();

			private:
				//////////////////////////////////////////////////////////////////////////
				Device(COM::iUnknown*);
				virtual ~Device();
				CPF_CLASSINSTANCE_ACCESS(Device);

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
							Graphics::iBlob* mpBlob;
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
