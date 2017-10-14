//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IntrusivePtr.hpp"
#include "Adapter/D3D12/DescriptorManager.hpp"
#include "Graphics.hpp"
#include "Graphics/iBlob.hpp"
#include <d3d12.h>
#include "Plugin/tClassInstance.hpp"


namespace CPF
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
		struct ResourceBindingDesc;
		struct RenderPassDesc;
		struct FrameBufferDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			class IndexBuffer;
			class VertexBuffer;

			static constexpr GOM::ClassID kDeviceCID = GOM::ClassID("Adapter::D3D12::Device"_crc64);

			class Device : public tRefCounted<Graphics::iDevice>
			{
			public:
				// Internal.
				GOM::Result Initialize(Plugin::iRegistry*, Graphics::iAdapter* adapter);

				// Overrides from iBase.
				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				// Overrides from iDevice.
				GOM::Result CPF_STDCALL Initialize() override;
				GOM::Result CPF_STDCALL Shutdown() override;

				GOM::Result CPF_STDCALL CreateSwapChain(Graphics::iInstance*, const Graphics::WindowData*, int32_t w, int32_t h, const Graphics::SwapChainDesc*, Graphics::iSwapChain**) override;
				GOM::Result CPF_STDCALL CreateCommandPool(Graphics::iCommandPool**) override;
				GOM::Result CPF_STDCALL CreateCommandBuffer(Graphics::iCommandPool*, Graphics::CommandBufferType type, Graphics::iCommandBuffer**) override;
				GOM::Result CPF_STDCALL CreateFence(int64_t initValue, Graphics::iFence**) override;
				GOM::Result CPF_STDCALL CreateImage2D(Graphics::HeapType heap, const Graphics::ImageDesc* desc, const Graphics::ClearValue* clearValue, Graphics::iImage**) override;
				GOM::Result CPF_STDCALL CreateShader(Graphics::iBlob* blob, Graphics::iShader**) override;
				GOM::Result CPF_STDCALL CreateResourceBinding(const Graphics::ResourceBindingDesc*, Graphics::iResourceBinding**) override;
				GOM::Result CPF_STDCALL CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding*, Graphics::iPipeline**) override;
				GOM::Result CPF_STDCALL CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** resource) override;
				GOM::Result CPF_STDCALL CreateSampler(const Graphics::SamplerDesc* desc, Graphics::iSampler** sampler) override;
				GOM::Result CPF_STDCALL CreateRenderPass(const Graphics::RenderPassDesc* desc, Graphics::iRenderPass** renderPass) override;
				GOM::Result CPF_STDCALL CreateFrameBuffer(const Graphics::FrameBufferDesc* desc, Graphics::iFrameBuffer** frameBuffer) override;

				GOM::Result CPF_STDCALL CreateIndexBuffer(const Graphics::ResourceDesc* desc, Graphics::Format format, Graphics::iIndexBuffer** indexBuffer) override;
				GOM::Result CPF_STDCALL CreateVertexBuffer(const Graphics::ResourceDesc* desc, int32_t stride, Graphics::iVertexBuffer** vertexBuffer) override;
				GOM::Result CPF_STDCALL CreateConstantBuffer(const Graphics::ResourceDesc*, const void* initData, Graphics::iConstantBuffer**) override;

				GOM::Result CPF_STDCALL CreateBlob(int64_t size, const void* data, Graphics::iBlob**) override;

				GOM::Result CPF_STDCALL CompileToByteCode(const char* entryPoint, Graphics::ShaderType type, size_t size, const char* source, Graphics::iBlob**) override;

				GOM::Result CPF_STDCALL CreateDepthStencilView(Graphics::iImage*, const Graphics::DepthStencilViewDesc*, Graphics::iImageView**) override;

				GOM::Result CPF_STDCALL Signal(Graphics::iFence*, int64_t value) override;
				void CPF_STDCALL Submit(int32_t count, Graphics::iCommandBuffer* const *) override;

				//////////////////////////////////////////////////////////////////////////
				// Internal
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
				Device(Plugin::iRegistry*, GOM::iUnknown*);
				virtual ~Device();
				CPF_CLASSINSTANCE_ACCESS(Device);

				IntrusivePtr<ID3D12Device> mpDevice;

				// TODO: Should probably be it's own class?
				IntrusivePtr<ID3D12CommandQueue> mpQueue;

				IntrusivePtr<Plugin::iRegistry> mpRegistry;
				DescriptorManager mShaderResourceDescriptors;
				DescriptorManager mSamplerDescriptors;
				DescriptorManager mRenderTargetDescriptors;
				DescriptorManager mDepthStencilDescriptors;
			};
		}
	}
}
