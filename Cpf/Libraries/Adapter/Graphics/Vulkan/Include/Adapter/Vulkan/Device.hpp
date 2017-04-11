//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Adapter/Vulkan.hpp"
#include "Graphics/Driver.hpp"
#include "VulkanUtils.hpp"
#include "Vector.hpp"


namespace Cpf
{
	namespace Graphics
	{
		namespace Driver
		{
			class iAdapter;
			class iCommandPool;
		}
	}
	namespace Adapters
	{
		namespace Vulkan
		{
			CPF_EXPORT_ADAPTERS_VULKAN class Device : public tRefCounted<Graphics::Driver::iDevice>
			{
			public:
				Device(Graphics::Driver::iAdapter* dev);
				virtual ~Device();

				bool CreateCommandPool(Graphics::Driver::iCommandPool**) override;
				bool CreateCommandBuffer(Graphics::Driver::iCommandPool*, Graphics::Driver::iCommandBuffer**) override;

				VkPhysicalDevice& GetPhysicalDevice() { return mPhysicalDevice; }
				VkDevice& GetDevice() { return mDevice; }

				Graphics::Driver::iAdapter* GetAdapter() const { return mpAdapter; }
				const Vector<VkPhysicalDevice>& GetDevices() const { return mDevices; }

				VkQueue& GetGraphicsQueue() { return mGraphicsQueue; }
				VkQueue& GetPresentQueue() { return mPresentQueue; }

				uint32_t& GetGraphicsQueueIndex() { return mGraphicsQueueIndex; }
				uint32_t& GetPresentQueueIndex() { return mPresentQueueIndex; }

			private:
				Graphics::Driver::iAdapter* mpAdapter;
				VkPhysicalDevice mPhysicalDevice;
				VkDevice mDevice;

				uint32_t mGraphicsQueueIndex;
				uint32_t mPresentQueueIndex;

				VkQueue mGraphicsQueue;
				VkQueue mPresentQueue;

				Vector<VkPhysicalDevice> mDevices;
			};
		}
	}
}
