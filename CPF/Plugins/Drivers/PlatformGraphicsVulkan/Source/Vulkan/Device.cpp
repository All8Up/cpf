//////////////////////////////////////////////////////////////////////////
#include "Vulkan/Device.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/Adapter.hpp"
#include "Vulkan/SwapChain.hpp"
#include "Vulkan/RenderPass.hpp"
#include "Vulkan/FrameBuffer.hpp"
#include "Vulkan/Fence.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/CommandPool.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "CPF/Platform/Graphics/ImageDesc.hpp"
#include "CPF/Platform/Graphics/DepthStencilViewDesc.hpp"

using namespace CPF;
using namespace Vulkan;

//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL Device::Initialize(Adapter* adapter)
{
	mPhysicalDevice = adapter->GetPhysicalDevice();

	// In Vulkan, we are creating a 'logical' device from the given physical device.
	VkPhysicalDeviceFeatures requiredFeatures;
	vkGetPhysicalDeviceFeatures(adapter->GetPhysicalDevice(), &requiredFeatures);

	// Queues
	STD::Vector<VkDeviceQueueCreateInfo> queueCreateInfo;
	{
		VkDeviceQueueCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.queueCount = 1;
		info.queueFamilyIndex = adapter->GetGraphicsQueueIndex();
		// TODO: This is incorrect but since it is always 1's, no worries for the moment.
		info.pQueuePriorities = adapter->GetQueuePriorities().data();

		queueCreateInfo.push_back(info);
	}

	// Get extensions from the device.
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(adapter->GetPhysicalDevice(), nullptr, &extensionCount, nullptr);
	mExtensions.resize(extensionCount);
	vkEnumerateDeviceExtensionProperties(adapter->GetPhysicalDevice(), nullptr, &extensionCount, mExtensions.data());

	STD::Vector<const char*> extensionNames = { "VK_KHR_swapchain" };

	VkDeviceCreateInfo deviceInfo = {};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.queueCreateInfoCount = uint32_t(queueCreateInfo.size());
	deviceInfo.pQueueCreateInfos = queueCreateInfo.data();
	deviceInfo.enabledExtensionCount = uint32_t(extensionNames.size());
	deviceInfo.ppEnabledExtensionNames = extensionNames.data();
	deviceInfo.pEnabledFeatures = &requiredFeatures;

	if (vkCreateDevice(adapter->GetPhysicalDevice(), &deviceInfo, nullptr, &mDevice) != VK_SUCCESS)
	{
		return GOM::kError;
	}
	vkGetDeviceQueue(mDevice, 0, 0, &mQueue);

	return GOM::kOK;
}

GOM::Result CPF_STDCALL Device::Shutdown()
{
	CPF_ASSERT_ALWAYS;
	return GOM::kNotImplemented;
}

//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL Device::CreateSwapChain(
	Graphics::iInstance* inst,
	const Graphics::WindowData* wd,
	int32_t w,
	int32_t h,
	const Graphics::SwapChainDesc* scd,
	Graphics::iSwapChain** sc
)
{
	SwapChain* vulkanSwapChain = new SwapChain();
	if (vulkanSwapChain)
	{
		const auto result = vulkanSwapChain->Initialize(static_cast<Instance*>(inst), this, wd, w, h, scd);
		if (GOM::Succeeded(result))
		{
			*sc = vulkanSwapChain;
			return result;
		}
		vulkanSwapChain->Release();
		return result;
	}
	return GOM::kOutOfMemory;
}

GOM::Result CPF_STDCALL Device::CreateCommandPool(Graphics::iCommandPool** ocp)
{
	if (ocp)
	{
		CommandPool* vulkanCommandPool = new CommandPool();
		if (vulkanCommandPool)
		{
			const auto result = vulkanCommandPool->Initialize(this);
			if (GOM::Succeeded(result))
			{
				*ocp = vulkanCommandPool;
				return result;
			}
			vulkanCommandPool->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::CreateCommandBuffer(
	Graphics::iCommandPool* cp,
	Graphics::CommandBufferType type,
	Graphics::iCommandBuffer** ocb)
{
	if (ocb)
	{
		CommandBuffer* vulkanCommandBuffer = new CommandBuffer();
		if (vulkanCommandBuffer)
		{
			const auto result = vulkanCommandBuffer->Initialize(this, static_cast<CommandPool*>(cp), type);
			if (GOM::Succeeded(result))
			{
				*ocb = vulkanCommandBuffer;
				return result;
			}
			vulkanCommandBuffer->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::CreateFence(bool signaled, Graphics::iFence** of)
{
	if (of)
	{
		Fence* vulkanFence = new Fence();
		if (vulkanFence)
		{
			const auto result = vulkanFence->Initialize(this, signaled);
			if (GOM::Succeeded(result))
			{
				*of = vulkanFence;
				return result;
			}
			vulkanFence->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::CreateImage2D(
	Graphics::HeapType heap,
	const Graphics::ImageDesc* desc,
	const Graphics::ClearValue* clearValue,
	Graphics::iImage** oi)
{
	if (oi)
	{
		Image* vulkanImage = new Image();
		if (vulkanImage)
		{
			const auto result = vulkanImage->Create2D(this, heap, clearValue, desc);
			if (GOM::Succeeded(result))
			{
				*oi = vulkanImage;
				return result;
			}
			vulkanImage->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::CreateShader(Graphics::iBlob* blob, Graphics::iShader** os)
{
	CPF_ASSERT_ALWAYS;
	(void)blob; (void)os;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateResourceBinding(
	const Graphics::ResourceBindingDesc* rbd, Graphics::iResourceBinding** orb)
{
	CPF_ASSERT_ALWAYS;
	(void)rbd; (void)orb;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreatePipeline(
	const Graphics::PipelineStateDesc* desc,
	Graphics::iResourceBinding* rb,
	Graphics::iPipeline** op
)
{
	CPF_ASSERT_ALWAYS;
	(void)desc; (void)rb; (void)op;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateResource(
	const Graphics::ResourceDesc* desc,
	Graphics::iResource** or
)
{
	CPF_ASSERT_ALWAYS;
	(void)desc; (void)or;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateSampler(
	const Graphics::SamplerDesc* desc,
	Graphics::iSampler** os
)
{
	CPF_ASSERT_ALWAYS;
	(void)desc; (void)os;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateRenderPass(
	const Graphics::RenderPassDesc* desc,
	Graphics::iRenderPass** orp
)
{
	if (desc && orp)
	{
		RenderPass* renderPass = new RenderPass();
		if (renderPass)
		{
			const auto result = renderPass->Initialize(this, desc);
			if (GOM::Succeeded(result))
			{
				*orp = renderPass;
				return result;
			}
			renderPass->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::CreateFrameBuffer(
	const Graphics::FrameBufferDesc* desc,
	Graphics::iFrameBuffer** outFrameBuffer
)
{
	if (desc && outFrameBuffer)
	{
		FrameBuffer* frameBuffer = new FrameBuffer();
		if (frameBuffer)
		{
			const auto result = frameBuffer->Initialize(this, desc);
			if (GOM::Succeeded(result))
			{
				*outFrameBuffer = frameBuffer;
				return result;
			}
			frameBuffer->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::CreateIndexBuffer(
	const Graphics::ResourceDesc* desc,
	Graphics::Format format,
	Graphics::iIndexBuffer** indexBuffer
)
{
	CPF_ASSERT_ALWAYS;
	(void)desc; (void)format; (void)indexBuffer;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateVertexBuffer(
	const Graphics::ResourceDesc* desc,
	int32_t stride,
	Graphics::iVertexBuffer** indexBuffer)
{
	CPF_ASSERT_ALWAYS;
	(void)desc; (void)stride; (void)indexBuffer;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateConstantBuffer(
	const Graphics::ResourceDesc* desc,
	const void* initData,
	Graphics::iConstantBuffer** ocb
)
{
	CPF_ASSERT_ALWAYS;
	(void)desc; (void)initData; (void)ocb;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateBlob(int64_t size, const void* data, Graphics::iBlob** ob)
{
	CPF_ASSERT_ALWAYS;
	(void)size; (void)data; (void)ob;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL Device::CreateDepthStencilView(
	Graphics::iImage* img,
	const Graphics::DepthStencilViewDesc* dsvd,
	Graphics::iImageView** oiv
)
{
	if (img && oiv)
	{
		ImageView* imageView = new ImageView();
		if (imageView)
		{
			Graphics::ImageDesc desc;
			img->GetDesc(&desc);
			const auto result = imageView->Initialize(this, img, ToVKFormat(desc.mFormat), true);
			if (GOM::Succeeded(result))
			{
				*oiv = imageView;
				return result;
			}
			imageView->Release();
			return result;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Device::Signal(Graphics::iFence* fence)
{
	vkQueueSubmit(mQueue, 0, nullptr, static_cast<Vulkan::Fence*>(fence)->GetVkFence());
	return GOM::kOK;
}

void CPF_STDCALL Device::Submit(int32_t count, Graphics::iCommandBuffer* const * ocb)
{
	STD::Vector<VkCommandBuffer> buffers;
	for (int i = 0; i < count; ++i)
		buffers.push_back(static_cast<CommandBuffer*>(ocb[i])->GetVkCommandBuffer());

	VkSubmitInfo submitInfo;
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;
	submitInfo.waitSemaphoreCount = 0;
	submitInfo.pWaitSemaphores = nullptr;
	submitInfo.pWaitDstStageMask = nullptr;
	submitInfo.commandBufferCount = count;
	submitInfo.pCommandBuffers = buffers.data();
	submitInfo.signalSemaphoreCount = 0;
	submitInfo.pSignalSemaphores = nullptr;

	vkQueueSubmit(mQueue, 1, &submitInfo, VK_NULL_HANDLE);
}

GOM::Result CPF_STDCALL Device::CompileToByteCode(
	const char* entryPoint,
	Graphics::ShaderType type,
	size_t size,
	const char* source,
	Graphics::iBlob** outBlob
)
{
	CPF_ASSERT_ALWAYS;
	(void)entryPoint; (void)type; (void)size; (void)source; (void)outBlob;
	return GOM::kNotImplemented;
}
