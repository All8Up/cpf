//////////////////////////////////////////////////////////////////////////
#include "Vulkan/SwapChain.hpp"
#include "Vulkan/Device.hpp"
#include "Vulkan/Instance.hpp"
#include "CPF/Logging.hpp"
#include "CPF/Platform/Graphics/WindowData.hpp"
#include "CPF/Platform/Graphics/SwapChainDesc.hpp"
#include "CPF/Math/Algorithm.hpp"

using namespace CPF;
using namespace Vulkan;

void CPF_STDCALL SwapChain::Present()
{
	vkWaitForFences(mpDevice->GetDevice(), 1, &mFences[mNextImage], false, std::numeric_limits<uint64_t>::max());
	vkResetFences(mpDevice->GetDevice(), 1, &mFences[mNextImage]);

	VkPresentInfoKHR presentInfo;
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = nullptr;
	presentInfo.waitSemaphoreCount = 0;
	presentInfo.pWaitSemaphores = nullptr;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &mSwapChain;
	presentInfo.pImageIndices = &mNextImage;
	presentInfo.pResults = nullptr;
	vkQueuePresentKHR(mSubmitQueue, &presentInfo);

	vkAcquireNextImageKHR(
		mpDevice->GetDevice(),
		mSwapChain,
		std::numeric_limits<uint64_t>::max(),
		nullptr,
		mFences[mNextImage],
		&mNextImage);
}

void CPF_STDCALL SwapChain::Resize(int32_t x, int32_t y)
{
	(void)x; (void)y;
	CPF_ASSERT_ALWAYS;
}

int32_t CPF_STDCALL SwapChain::GetCurrentIndex()
{
	return int32_t(mNextImage);
}

Graphics::iImage* CPF_STDCALL SwapChain::GetImage(int32_t index)
{
	if (index < 0 || index >= int32_t(mpImages.size()))
		return nullptr;
	mpImages[index]->AddRef();
	return mpImages[index];
}

Graphics::iImageView* CPF_STDCALL SwapChain::GetImageView(int32_t index)
{
	if (index < 0 || index >= int32_t(mpImageViews.size()))
		return nullptr;
	mpImageViews[index]->AddRef();
	return mpImageViews[index];
}

//
GOM::Result SwapChain::Initialize(Instance* inst, Device* device, const Graphics::WindowData* wd, int32_t w, int32_t h, const Graphics::SwapChainDesc* scd)
{
	// Store off the device.
	mpDevice = device;

	//
	vkGetDeviceQueue(device->GetDevice(), 0, 0, &mSubmitQueue);

	// Create the associated presentation surface.
	VkWin32SurfaceCreateInfoKHR presentationSurfaceCreateInfo;
	presentationSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	presentationSurfaceCreateInfo.pNext = nullptr;
	presentationSurfaceCreateInfo.flags = 0;
	presentationSurfaceCreateInfo.hinstance = GetModuleHandle(nullptr);
	presentationSurfaceCreateInfo.hwnd = wd->mHWnd;

	VkResult result = vkCreateWin32SurfaceKHR(inst->GetInstance(), &presentationSurfaceCreateInfo, nullptr, &mPresentationSurface);
	if (result != VK_SUCCESS)
		return GOM::kError;

	// Query the surface for capabilities.
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->GetPhysicalDevice(), mPresentationSurface, &surfaceCapabilities);
	CPF_ASSERT(surfaceCapabilities.supportedUsageFlags & (VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT));

	// TODO: While they should match, perhaps this should always use the w/h values?
	VkExtent2D swapchainExtent;
	if (surfaceCapabilities.currentExtent.width == uint32_t(-1))
	{
		swapchainExtent.width = w;
		swapchainExtent.height = h;
	}
	else
	{
		swapchainExtent = surfaceCapabilities.currentExtent;
	}

	const VkFormat requestedFormat = ToVKFormat(scd->mFormat);
	// TODO: What about HDR displays?
	const VkColorSpaceKHR requestedColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;

	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->GetPhysicalDevice(), mPresentationSurface, &formatCount, nullptr);
	STD::Vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->GetPhysicalDevice(), mPresentationSurface, &formatCount, surfaceFormats.data());

	VkBool32 supported = false;
	vkGetPhysicalDeviceSurfaceSupportKHR(device->GetPhysicalDevice(), 0, mPresentationSurface, &supported);

	bool formatValid = false;
	for (const VkSurfaceFormatKHR& format : surfaceFormats)
	{
		if (format.format == requestedFormat && format.colorSpace == requestedColorSpace)
		{
			formatValid = true;
			break;
		}
	}

	if (formatValid == false)
	{
		CPF_LOG(Vulkan, Error) << "Requested SwapChain format is not available";
		return GOM::kError;
	}

	// Select present mode
	uint32_t presentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->GetPhysicalDevice(), mPresentationSurface, &presentModeCount, nullptr);
	std::vector<VkPresentModeKHR> presentModes(presentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->GetPhysicalDevice(), mPresentationSurface, &presentModeCount, presentModes.data());

	// Select present mode, FIFO for VSync, otherwise preferring MAILBOX -> IMMEDIATE -> FIFO
	VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
	if (scd->mVSync == false)
	{
		for (size_t i = 0; i < presentModeCount; i++)
		{
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
				break;
			}
			if (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR)
			{
				presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			}
		}
	}

	// Swapchain Creation
	VkSwapchainCreateInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	info.surface = mPresentationSurface;
	const uint32_t maxImageCount = surfaceCapabilities.maxImageCount ? surfaceCapabilities.maxImageCount : UINT32_MAX; // 0 means no limit on the number of images
	info.minImageCount = Math::Clamp(uint32_t(scd->mBackBufferCount), surfaceCapabilities.minImageCount, maxImageCount);
	info.imageFormat = requestedFormat;
	info.imageColorSpace = requestedColorSpace;
	info.imageExtent = { swapchainExtent.width, swapchainExtent.height };
	info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	info.preTransform = surfaceCapabilities.currentTransform;
	info.imageArrayLayers = 1;
	info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	info.queueFamilyIndexCount = 0;     // Only needed if VK_SHARING_MODE_CONCURRENT
	info.pQueueFamilyIndices = nullptr; // Only needed if VK_SHARING_MODE_CONCURRENT
	info.presentMode = presentMode;
	info.clipped = true;
	info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	info.oldSwapchain = nullptr;

	if (vkCreateSwapchainKHR(device->GetDevice(), &info, nullptr, &mSwapChain)!=VK_SUCCESS)
	{
		CPF_LOG(Vulkan, Error) << "Could not create swapchain.";
		return false;
	}

	uint32_t imageCount = 0;
	vkGetSwapchainImagesKHR(device->GetDevice(), mSwapChain, &imageCount, nullptr);
	STD::Vector<VkImage> images(imageCount);
	vkGetSwapchainImagesKHR(device->GetDevice(), mSwapChain, &imageCount, images.data());

	mpImages.clear();
	mpImageViews.clear();
	for (const auto& vkImage : images)
	{
		Image* image = new Image();
		ImageView* imageView = new ImageView();
		if (image && imageView &&
			image->Initialize(vkImage) && imageView->Initialize(device, image, requestedFormat))
		{
			mpImages.push_back(IntrusivePtr<Graphics::iImage>(image));
			mpImageViews.push_back(IntrusivePtr<Graphics::iImageView>(imageView));

			VkFence fence;
			VkFenceCreateInfo fenceCreateInfo;
			fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceCreateInfo.pNext = nullptr;
			fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
			vkCreateFence(device->GetDevice(), &fenceCreateInfo, nullptr, &fence);
			mFences.push_back(fence);
		}
	}

	VkFence fence;
	VkFenceCreateInfo fenceCreateInfo;
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.pNext = nullptr;
	fenceCreateInfo.flags = 0;
	vkCreateFence(device->GetDevice(), &fenceCreateInfo, nullptr, &fence);
	if (vkAcquireNextImageKHR(
		device->GetDevice(),
		mSwapChain,
		std::numeric_limits<uint64_t>::max(),
		nullptr,
		fence,
		&mNextImage) != VK_SUCCESS)
		return GOM::kError;
	vkWaitForFences(device->GetDevice(), 1, &fence, false, std::numeric_limits<uint64_t>::max());
	vkDestroyFence(device->GetDevice(), fence, nullptr);

	return GOM::kOK;
}
