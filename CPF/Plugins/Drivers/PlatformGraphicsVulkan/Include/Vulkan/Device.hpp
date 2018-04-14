//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iDevice.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Std/Vector.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Vulkan
	{
		class Instance;
		class Adapter;

		class Device final : public GOM::tUnknown<Graphics::iDevice>
		{
		public:
			//
			Device() = default;

			// Internal.
			GOM::Result CPF_STDCALL Initialize(Adapter* adapter);
			GOM::Result CPF_STDCALL Shutdown();
			VkDevice GetDevice() const { return mDevice; }
			VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }

			// Overrides from iDevice.
			GOM::Result CPF_STDCALL CreateSwapChain(Graphics::iInstance* inst, const Graphics::WindowData* wd, int32_t w, int32_t h, const Graphics::SwapChainDesc* scd, Graphics::iSwapChain** sc) override;
			GOM::Result CPF_STDCALL CreateCommandPool(Graphics::iCommandPool** ocp) override;
			GOM::Result CPF_STDCALL CreateCommandBuffer(Graphics::iCommandPool* cp, Graphics::CommandBufferType type, Graphics::iCommandBuffer** ocb) override;
			GOM::Result CPF_STDCALL CreateFence(bool signaled, Graphics::iFence** of) override;
			GOM::Result CPF_STDCALL CreateImage2D(Graphics::HeapType heap, const Graphics::ImageDesc* desc, const Graphics::ClearValue* clearValue, Graphics::iImage** oi) override;
			GOM::Result CPF_STDCALL CreateShader(Graphics::iBlob* blob, Graphics::iShader** os) override;
			GOM::Result CPF_STDCALL CreateResourceBinding(const Graphics::ResourceBindingDesc* rbd, Graphics::iResourceBinding** orb) override;
			GOM::Result CPF_STDCALL CreatePipeline(const Graphics::PipelineStateDesc* desc, Graphics::iResourceBinding* rb, Graphics::iPipeline** op) override;
			GOM::Result CPF_STDCALL CreateResource(const Graphics::ResourceDesc* desc, Graphics::iResource** or ) override;
			GOM::Result CPF_STDCALL CreateSampler(const Graphics::SamplerDesc* desc, Graphics::iSampler** os) override;
			GOM::Result CPF_STDCALL CreateRenderPass(const Graphics::RenderPassDesc* desc, Graphics::iRenderPass** orp) override;
			GOM::Result CPF_STDCALL CreateFrameBuffer(const Graphics::FrameBufferDesc* desc, Graphics::iFrameBuffer** frameBuffer) override;
			GOM::Result CPF_STDCALL CreateIndexBuffer(const Graphics::ResourceDesc* desc, Graphics::Format format, Graphics::iIndexBuffer** indexBuffer) override;
			GOM::Result CPF_STDCALL CreateVertexBuffer(const Graphics::ResourceDesc* desc, int32_t stride, Graphics::iVertexBuffer** indexBuffer) override;
			GOM::Result CPF_STDCALL CreateConstantBuffer(const Graphics::ResourceDesc* desc, const void* initData, Graphics::iConstantBuffer** ocb) override;
			GOM::Result CPF_STDCALL CreateBlob(int64_t size, const void* data, Graphics::iBlob** ob) override;
			GOM::Result CPF_STDCALL CreateDepthStencilView(Graphics::iImage* img, const Graphics::DepthStencilViewDesc* dsvd, Graphics::iImageView** oiv) override;
			GOM::Result CPF_STDCALL Signal(Graphics::iFence* fence) override;
			void CPF_STDCALL Submit(int32_t count, Graphics::iCommandBuffer* const * ocb) override;
			GOM::Result CPF_STDCALL CompileToByteCode(const char* entryPoint, Graphics::ShaderType type, size_t size, const char* source, Graphics::iBlob** outBlob) override;

		private:
			VkDevice mDevice;
			VkPhysicalDevice mPhysicalDevice;
			STD::Vector<VkExtensionProperties> mExtensions;
			VkQueue mQueue;
		};
	}
}
