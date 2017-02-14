//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iSwapChain.hpp"
#include "RefCounted.hpp"
#include "VulkanUtils.hpp"
#include "Vector.hpp"


namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		namespace Driver
		{
			class iDevice;
		}
	}

	namespace Adapters
	{
		namespace Vulkan
		{
			class Instance;
			class Device;

			class SwapChain : public tRefCounted<Graphics::Driver::iSwapChain>
			{
			public:
				SwapChain(Instance*, Graphics::Driver::iDevice*, iWindow*, const Graphics::Driver::SwapChainDesc& desc);
				~SwapChain() override;

				VkSwapchainKHR& GetSwapChain() { return mSwapChain; }
				VkSemaphore& GetImageAvailableSemaphore() { return mImageAvailableSemaphore; }
				VkSemaphore& GetRenderingFinishedSemaphore() { return mRenderingFinishedSemaphore; }

				bool OnWindowSizeChanged();

				VkSurfaceFormatKHR GetFormat() const { return mFormat; }

				int32_t GetNextBackBufferIndex();
				VkImage GetBackBuffer(int32_t idx);
				VkImage GetNextBackBuffer();
				VkImageView GetImageView(int32_t idx);
				uint32_t GetWidth() const { return mExtents.width; }
				uint32_t GetHeight() const { return mExtents.height; }

			private:
				bool _CreateDevice(Instance* instance, Graphics::Driver::iDevice* device);
				bool _CreatePresentationSurface(Instance* instance, iWindow* window);
				bool _CreateSwapChain(Device* device);
				bool _CheckPhysicalDeviceProperties(VkPhysicalDevice physical_device, uint32_t &selected_graphics_queue_family_index, uint32_t &selected_present_queue_family_index);
				uint32_t _GetSwapChainNumImages(VkSurfaceCapabilitiesKHR &surface_capabilities);
				VkSurfaceFormatKHR _GetSwapChainFormat(std::vector<VkSurfaceFormatKHR> &surface_formats);
				VkExtent2D _GetSwapChainExtent(VkSurfaceCapabilitiesKHR &surface_capabilities);
				VkImageUsageFlags _GetSwapChainUsageFlags(VkSurfaceCapabilitiesKHR &surface_capabilities);
				VkSurfaceTransformFlagBitsKHR _GetSwapChainTransform(VkSurfaceCapabilitiesKHR &surface_capabilities);
				VkPresentModeKHR _GetSwapChainPresentMode(std::vector<VkPresentModeKHR> &present_modes);
				bool _GetDeviceQueue(Device* device);
				bool _CreateSemaphores(Device* device);

				Device* mpDevice;
				Graphics::Driver::SwapChainDesc mDesc;
				VkSurfaceKHR mPresentationSurface;
				VkSurfaceFormatKHR mFormat;
				VkSwapchainKHR mSwapChain;

				VkSemaphore mImageAvailableSemaphore;
				VkSemaphore mRenderingFinishedSemaphore;

				VkExtent2D mExtents;

				Vector<VkImage> mBackBuffers;
				Vector<VkImageView> mViews;
			};
		}
	}
}
