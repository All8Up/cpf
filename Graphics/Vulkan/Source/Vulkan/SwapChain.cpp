//////////////////////////////////////////////////////////////////////////
#include "Adapters/Vulkan/SwapChain.hpp"
#include "Adapters/Vulkan/Instance.hpp"
#include "Adapters/Vulkan/Device.hpp"
#include "Adapters/Vulkan/Adapter.hpp"
#include "Application/Application.hpp"
#include <iostream>

using namespace Cpf;
using namespace Adapters;
using namespace Vulkan;

SwapChain::SwapChain(Instance* instance, Graphics::Driver::iDevice* device, iWindow* window, const Graphics::Driver::SwapChainDesc& desc)
	: mpDevice(static_cast<Device*>(device))
	, mDesc(desc)
	, mSwapChain(nullptr)
	, mExtents{ 640, 480 }
{
	(void)desc;
	if (!_CreatePresentationSurface(instance, window))
		return;
	if (!_CreateDevice(instance, mpDevice))
		return;
	if (!_CreateSemaphores(mpDevice))
		return;
	if (!_CreateSwapChain(mpDevice))
		return;
	if (!_GetDeviceQueue(mpDevice))
		return;
}

SwapChain::~SwapChain()
{
	Adapter* vAdapter = static_cast<Adapter*>(mpDevice->GetAdapter());
	Instance* vInstance = static_cast<Instance*>(vAdapter->GetInstance());

	vkDestroySurfaceKHR(vInstance->GetInstance(), mPresentationSurface, nullptr);
	vkDestroySwapchainKHR(mpDevice->GetDevice(), mSwapChain, nullptr);
	vkDestroySemaphore(mpDevice->GetDevice(), mImageAvailableSemaphore, nullptr);
	vkDestroySemaphore(mpDevice->GetDevice(), mRenderingFinishedSemaphore, nullptr);
}

//////////////////////////////////////////////////////////////////////////
bool SwapChain::_CreateDevice(Instance* instance, Graphics::Driver::iDevice* device)
{
	Device* vulkanDevice = static_cast<Device*>(device);

	uint32_t num_devices = 0;
	if ((vkEnumeratePhysicalDevices(instance->GetInstance(), &num_devices, nullptr) != VK_SUCCESS) || (num_devices == 0))
	{
		return false;
	}

	std::vector<VkPhysicalDevice> physical_devices(num_devices);
	if (vkEnumeratePhysicalDevices(instance->GetInstance(), &num_devices, &physical_devices[0]) != VK_SUCCESS)
	{
		return false;
	}

	uint32_t selected_graphics_queue_family_index = UINT32_MAX;
	uint32_t selected_present_queue_family_index = UINT32_MAX;

	for (uint32_t i = 0; i < num_devices; ++i)
	{
		if (_CheckPhysicalDeviceProperties(physical_devices[i], selected_graphics_queue_family_index, selected_present_queue_family_index))
		{
			vulkanDevice->GetPhysicalDevice() = physical_devices[i];
		}
	}
	if (vulkanDevice->GetPhysicalDevice() == VK_NULL_HANDLE)
	{
		return false;
	}

	std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
	std::vector<float> queue_priorities = { 1.0f };

	queue_create_infos.push_back(
	{
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		nullptr,
		0,
		selected_graphics_queue_family_index,
		static_cast<uint32_t>(queue_priorities.size()),
		&queue_priorities[0]
	});

	if (selected_graphics_queue_family_index != selected_present_queue_family_index)
	{
		queue_create_infos.push_back(
		{
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			nullptr,
			0,
			selected_present_queue_family_index,
			static_cast<uint32_t>(queue_priorities.size()),
			&queue_priorities[0]
		});
	}

	std::vector<const char*> extensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkDeviceCreateInfo device_create_info =
	{
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		nullptr,
		0,
		static_cast<uint32_t>(queue_create_infos.size()),
		&queue_create_infos[0],
		0,
		nullptr,
		static_cast<uint32_t>(extensions.size()),
		&extensions[0],
		nullptr
	};

	if (vkCreateDevice(vulkanDevice->GetPhysicalDevice(), &device_create_info, nullptr, &vulkanDevice->GetDevice()) != VK_SUCCESS) {
		std::cout << "Could not create Vulkan device!" << std::endl;
		return false;
	}

	vulkanDevice->GetGraphicsQueueIndex() = selected_graphics_queue_family_index;
	vulkanDevice->GetPresentQueueIndex() = selected_present_queue_family_index;
	return true;
}

bool SwapChain::_CreatePresentationSurface(Instance* instance, iWindow* window)
{
	OSWindowData windowData = window->GetOSWindowData();
	Instance* vulkanInstance = static_cast<Instance*>(instance);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surface_create_info =
	{
		VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		nullptr,
		0,
		GetModuleHandle(nullptr),
		windowData.mHwnd
	};

	if (vkCreateWin32SurfaceKHR(vulkanInstance->GetInstance(), &surface_create_info, nullptr, &mPresentationSurface) == VK_SUCCESS)
	{
		return true;
	}

#elif defined(VK_USE_PLATFORM_XCB_KHR)
	VkXcbSurfaceCreateInfoKHR surface_create_info =
	{
		VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
		nullptr,
		0,
		Window.Connection,
		Window.Handle
	};

	if (vkCreateXcbSurfaceKHR(Vulkan.Instance, &surface_create_info, nullptr, &Vulkan.PresentationSurface) == VK_SUCCESS) {
		return true;
	}

#elif defined(VK_USE_PLATFORM_XLIB_KHR)
	VkXlibSurfaceCreateInfoKHR surface_create_info =
	{
		VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
		nullptr,
		0,
		Window.DisplayPtr,
		Window.Handle
	};
	if (vkCreateXlibSurfaceKHR(Vulkan.Instance, &surface_create_info, nullptr, &Vulkan.PresentationSurface) == VK_SUCCESS)
	{
		return true;
	}

#endif

//	std::cout << "Could not create presentation surface!" << std::endl;
	return false;
}

bool SwapChain::_GetDeviceQueue(Device* device)
{
	vkGetDeviceQueue(device->GetDevice(), device->GetGraphicsQueueIndex(), 0, &device->GetGraphicsQueue());
	vkGetDeviceQueue(device->GetDevice(), device->GetPresentQueueIndex(), 0, &device->GetPresentQueue());
	return true;
}

bool SwapChain::_CreateSemaphores(Device* device)
{
	VkSemaphoreCreateInfo semaphore_create_info = {
		VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		nullptr,
		0
	};

	if ((vkCreateSemaphore(device->GetDevice(), &semaphore_create_info, nullptr, &mImageAvailableSemaphore) != VK_SUCCESS) ||
		(vkCreateSemaphore(device->GetDevice(), &semaphore_create_info, nullptr, &mRenderingFinishedSemaphore) != VK_SUCCESS))
	{
		return false;
	}

	return true;
}

bool SwapChain::OnWindowSizeChanged()
{
	Device* vulkanDevice = static_cast<Device*>(mpDevice);
//	_Clear(vulkanDevice);

	if (!_CreateSwapChain(vulkanDevice)) {
		return false;
	}
//	if (!_CreateCommandBuffers(vulkanDevice)) {
//		return false;
//	}
	return true;
}

int32_t SwapChain::GetNextBackBufferIndex()
{
	Device* vulkanDevice = static_cast<Device*>(mpDevice);

	uint32_t image_index;
	VkResult result = vkAcquireNextImageKHR(
		vulkanDevice->GetDevice(),
		mSwapChain,
		UINT64_MAX,
		mImageAvailableSemaphore,
		VK_NULL_HANDLE,
		&image_index);
	switch (result)
	{
	case VK_SUCCESS:
	case VK_SUBOPTIMAL_KHR:
		break;
	case VK_ERROR_OUT_OF_DATE_KHR:
		OnWindowSizeChanged();
		return 0;
	default:
		return 0;
	}

	return image_index;
}

VkImage SwapChain::GetNextBackBuffer()
{
	int32_t nextImage = GetNextBackBufferIndex();
	return mBackBuffers[nextImage];
}

VkImage SwapChain::GetBackBuffer(int32_t idx)
{
	return mBackBuffers[idx];
}

VkImageView SwapChain::GetImageView(int32_t idx)
{
	return mViews[idx];
}

bool SwapChain::_CreateSwapChain(Device* device)
{
	if (device->GetDevice() != VK_NULL_HANDLE)
	{
		vkDeviceWaitIdle(device->GetDevice());
	}

	VkSurfaceCapabilitiesKHR surface_capabilities;
	if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->GetPhysicalDevice(), mPresentationSurface, &surface_capabilities) != VK_SUCCESS)
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	uint32_t formats_count;
	if ((vkGetPhysicalDeviceSurfaceFormatsKHR(device->GetPhysicalDevice(), mPresentationSurface, &formats_count, nullptr) != VK_SUCCESS) || (formats_count == 0))
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	std::vector<VkSurfaceFormatKHR> surface_formats(formats_count);
	if (vkGetPhysicalDeviceSurfaceFormatsKHR(device->GetPhysicalDevice(), mPresentationSurface, &formats_count, &surface_formats[0]) != VK_SUCCESS)
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	uint32_t present_modes_count;
	if ((vkGetPhysicalDeviceSurfacePresentModesKHR(device->GetPhysicalDevice(), mPresentationSurface, &present_modes_count, nullptr) != VK_SUCCESS) || (present_modes_count == 0))
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	std::vector<VkPresentModeKHR> present_modes(present_modes_count);
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(device->GetPhysicalDevice(), mPresentationSurface, &present_modes_count, &present_modes[0]) != VK_SUCCESS)
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	uint32_t                      desired_number_of_images = _GetSwapChainNumImages(surface_capabilities);
	mFormat = _GetSwapChainFormat(surface_formats);
	_GetSwapChainExtent(surface_capabilities);
	VkImageUsageFlags             desired_usage = _GetSwapChainUsageFlags(surface_capabilities);
	VkSurfaceTransformFlagBitsKHR desired_transform = _GetSwapChainTransform(surface_capabilities);
	VkPresentModeKHR              desired_present_mode = _GetSwapChainPresentMode(present_modes);
	VkSwapchainKHR                old_swap_chain = mSwapChain;

	if (static_cast<int>(desired_usage) == -1)
	{
		return false;
	}
	if (static_cast<int>(desired_present_mode) == -1)
	{
		return false;
	}
	if ((mExtents.width == 0) || (mExtents.height == 0))
	{
		// Current surface size is (0, 0) so we can't create a swap chain and render anything (CanRender == false)
		// But we don't wont to kill the application as this situation may occur i.e. when window gets minimized
		return true;
	}

	VkSwapchainCreateInfoKHR swap_chain_create_info =
	{
		VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		nullptr,
		0,
		mPresentationSurface,
		desired_number_of_images,
		mFormat.format,
		mFormat.colorSpace,
		mExtents,
		1,
		desired_usage,
		VK_SHARING_MODE_EXCLUSIVE,
		0,
		nullptr,
		desired_transform,
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		desired_present_mode,
		VK_TRUE,
		old_swap_chain
	};

	if (vkCreateSwapchainKHR(device->GetDevice(), &swap_chain_create_info, nullptr, &mSwapChain) != VK_SUCCESS)
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}
	if (old_swap_chain != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(device->GetDevice(), old_swap_chain, nullptr);
	}


	//////////////////////////////////////////////////////////////////////////
	mBackBuffers.resize(desired_number_of_images);
	if (vkGetSwapchainImagesKHR(device->GetDevice(), mSwapChain, &desired_number_of_images, &mBackBuffers[0]) != VK_SUCCESS)
	{
		return false;
	}

	mViews.resize(desired_number_of_images);
	for (uint32_t i=0; i<desired_number_of_images; ++i)
	{
		VkImageViewCreateInfo viewInfo =
		{
			VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,	// VkStructureType            sType;
			nullptr,									// const void*                pNext;
			0,											// VkImageViewCreateFlags     flags;
			mBackBuffers[i],							// VkImage                    image;
			VK_IMAGE_VIEW_TYPE_2D,						// VkImageViewType            viewType;
			mFormat.format,								// VkFormat                   format;
			{											// VkComponentMapping         components;
				VK_COMPONENT_SWIZZLE_IDENTITY,				// VkComponentSwizzle    r;
				VK_COMPONENT_SWIZZLE_IDENTITY,				// VkComponentSwizzle    g;
				VK_COMPONENT_SWIZZLE_IDENTITY,				// VkComponentSwizzle    b;
				VK_COMPONENT_SWIZZLE_IDENTITY				// VkComponentSwizzle    a;
			},
			{											// VkImageSubresourceRange    subresourceRange;
				VK_IMAGE_ASPECT_COLOR_BIT,					// VkImageAspectFlags    aspectMask;
				0,											// uint32_t              baseMipLevel;
				1,											// uint32_t              levelCount;
				0,											// uint32_t              baseArrayLayer;
				1											// uint32_t              layerCount;
			}
		};
		vkCreateImageView(device->GetDevice(), &viewInfo, nullptr, &mViews[i]);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool SwapChain::_CheckPhysicalDeviceProperties(VkPhysicalDevice physical_device, uint32_t &selected_graphics_queue_family_index, uint32_t &selected_present_queue_family_index)
{
	uint32_t extensions_count = 0;
	if ((vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extensions_count, nullptr) != VK_SUCCESS) || (extensions_count == 0))
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	std::vector<VkExtensionProperties> available_extensions(extensions_count);
	if (vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extensions_count, &available_extensions[0]) != VK_SUCCESS)
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	std::vector<const char*> device_extensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	for (size_t i = 0; i < device_extensions.size(); ++i)
	{
		if (!CheckExtensionAvailability(device_extensions[i], available_extensions))
		{
			CPF_ASSERT_ALWAYS;
			return false;
		}
	}

	VkPhysicalDeviceProperties device_properties;
	VkPhysicalDeviceFeatures device_features;

	vkGetPhysicalDeviceProperties(physical_device, &device_properties);
	vkGetPhysicalDeviceFeatures(physical_device, &device_features);

	uint32_t major_version = VK_VERSION_MAJOR(device_properties.apiVersion);

	if ((major_version < 1) || (device_properties.limits.maxImageDimension2D < 4096))
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	uint32_t queue_families_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_families_count, nullptr);
	if (queue_families_count == 0)
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	std::vector<VkQueueFamilyProperties> queue_family_properties(queue_families_count);
	std::vector<VkBool32> queue_present_support(queue_families_count);

	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_families_count, &queue_family_properties[0]);

	uint32_t graphics_queue_family_index = UINT32_MAX;
	uint32_t present_queue_family_index = UINT32_MAX;

	for (uint32_t i = 0; i < queue_families_count; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, mPresentationSurface, &queue_present_support[i]);

		if ((queue_family_properties[i].queueCount > 0) && (queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
		{
			// Select first queue that supports graphics
			if (graphics_queue_family_index == UINT32_MAX)
			{
				graphics_queue_family_index = i;
			}

			// If there is queue that supports both graphics and present - prefer it
			if (queue_present_support[i])
			{
				selected_graphics_queue_family_index = i;
				selected_present_queue_family_index = i;
				return true;
			}
		}
	}

	// We don't have queue that supports both graphics and present so we have to use separate queues
	for (uint32_t i = 0; i < queue_families_count; ++i)
	{
		if (queue_present_support[i])
		{
			present_queue_family_index = i;
			break;
		}
	}

	// If this device doesn't support queues with graphics and present capabilities don't use it
	if ((graphics_queue_family_index == UINT32_MAX) || (present_queue_family_index == UINT32_MAX))
	{
		CPF_ASSERT_ALWAYS;
		return false;
	}

	selected_graphics_queue_family_index = graphics_queue_family_index;
	selected_present_queue_family_index = present_queue_family_index;
	return true;
}


//////////////////////////////////////////////////////////////////////////
uint32_t SwapChain::_GetSwapChainNumImages(VkSurfaceCapabilitiesKHR &surface_capabilities)
{
	// Set of images defined in a swap chain may not always be available for application to render to:
	// One may be displayed and one may wait in a queue to be presented
	// If application wants to use more images at the same time it must ask for more images
	uint32_t image_count = surface_capabilities.minImageCount + 1;
	if (mDesc.mBackBufferCount >= int32_t(surface_capabilities.minImageCount) &&
		mDesc.mBackBufferCount <= int32_t(surface_capabilities.maxImageCount))
		image_count = mDesc.mBackBufferCount;

	if ((surface_capabilities.maxImageCount > 0) && (image_count > surface_capabilities.maxImageCount))
	{
		image_count = surface_capabilities.maxImageCount;
	}
	return image_count;
}

VkSurfaceFormatKHR SwapChain::_GetSwapChainFormat(std::vector<VkSurfaceFormatKHR> &surface_formats)
{
	// If the list contains only one entry with undefined format
	// it means that there are no preferred surface formats and any can be chosen
	if ((surface_formats.size() == 1) && (surface_formats[0].format == VK_FORMAT_UNDEFINED))
	{
		return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
	}

	// Check if list contains most widely used R8 G8 B8 A8 format
	// with nonlinear color space
	for (VkSurfaceFormatKHR &surface_format : surface_formats)
	{
		if (surface_format.format == VK_FORMAT_R8G8B8A8_UNORM)
		{
			return surface_format;
		}
	}

	// Return the first format from the list
	return surface_formats[0];
}

VkExtent2D SwapChain::_GetSwapChainExtent(VkSurfaceCapabilitiesKHR &surface_capabilities)
{
	// Special value of surface extent is width == height == -1
	// If this is so we define the size by ourselves but it must fit within defined confines
	if (surface_capabilities.currentExtent.width == -1)
	{
		mExtents = { 640, 480 };
		if (mExtents.width < surface_capabilities.minImageExtent.width)
		{
			mExtents.width = surface_capabilities.minImageExtent.width;
		}
		if (mExtents.height < surface_capabilities.minImageExtent.height)
		{
			mExtents.height = surface_capabilities.minImageExtent.height;
		}
		if (mExtents.width > surface_capabilities.maxImageExtent.width)
		{
			mExtents.width = surface_capabilities.maxImageExtent.width;
		}
		if (mExtents.height > surface_capabilities.maxImageExtent.height)
		{
			mExtents.height = surface_capabilities.maxImageExtent.height;
		}
		return mExtents;
	}

	// Most of the cases we define size of the swap_chain images equal to current window's size
	return surface_capabilities.currentExtent;
}

VkImageUsageFlags SwapChain::_GetSwapChainUsageFlags(VkSurfaceCapabilitiesKHR &surface_capabilities)
{
	// Color attachment flag must always be supported
	// We can define other usage flags but we always need to check if they are supported
	if (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	{
		return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	}
	/*
	std::cout << "VK_IMAGE_USAGE_TRANSFER_DST image usage is not supported by the swap chain!" << std::endl
		<< "Supported swap chain's image usages include:" << std::endl
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT ? "    VK_IMAGE_USAGE_TRANSFER_SRC\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT ? "    VK_IMAGE_USAGE_TRANSFER_DST\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_SAMPLED_BIT ? "    VK_IMAGE_USAGE_SAMPLED\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_STORAGE_BIT ? "    VK_IMAGE_USAGE_STORAGE\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_COLOR_ATTACHMENT\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT\n" : "")
		<< (surface_capabilities.supportedUsageFlags & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_INPUT_ATTACHMENT" : "")
		<< std::endl;
		*/
	return static_cast<VkImageUsageFlags>(-1);
}

VkSurfaceTransformFlagBitsKHR SwapChain::_GetSwapChainTransform(VkSurfaceCapabilitiesKHR &surface_capabilities)
{
	// Sometimes images must be transformed before they are presented (i.e. due to device's orienation
	// being other than default orientation)
	// If the specified transform is other than current transform, presentation engine will transform image
	// during presentation operation; this operation may hit performance on some platforms
	// Here we don't want any transformations to occur so if the identity transform is supported use it
	// otherwise just use the same transform as current transform
	if (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		return VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		return surface_capabilities.currentTransform;
	}
}

VkPresentModeKHR SwapChain::_GetSwapChainPresentMode(std::vector<VkPresentModeKHR> &present_modes)
{
	// FIFO present mode is always available
	// MAILBOX is the lowest latency V-Sync enabled mode (something like triple-buffering) so use it if available
	for (VkPresentModeKHR &present_mode : present_modes)
	{
		if (present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return present_mode;
		}
	}
	for (VkPresentModeKHR &present_mode : present_modes)
	{
		if (present_mode == VK_PRESENT_MODE_FIFO_KHR)
		{
			return present_mode;
		}
	}
//	std::cout << "FIFO present mode is not supported by the swap chain!" << std::endl;
	return static_cast<VkPresentModeKHR>(-1);
}
