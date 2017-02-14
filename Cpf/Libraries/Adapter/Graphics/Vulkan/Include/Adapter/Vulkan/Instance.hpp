//////////////////////////////////////////////////////////////////////////
#pragma once
#include "VulkanUtils.hpp"
#include "Graphics/Driver/iInstance.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		namespace Driver
		{
			class iDevice;
			class iAdapter;
			class iSwapChain;
			struct SwapChainDesc;
		}
	}
	namespace Adapters
	{
		namespace Vulkan
		{
			//////////////////////////////////////////////////////////////////////////
			class Instance : public tRefCounted<Graphics::Driver::iInstance>
			{
			public:
				static void* Create();

				bool EnumerateAdapters(int& count, Graphics::Driver::iAdapter** adapters) override;
				bool CreateDevice(Graphics::Driver::iAdapter* adapter, Graphics::Driver::iDevice**) override;
				bool CreateSwapChain(Graphics::Driver::iDevice*, iWindow*, const Graphics::Driver::SwapChainDesc&, Graphics::Driver::iSwapChain**) override;

				VkInstance GetInstance() const { return mInstance; }

			private:
				Instance();
				~Instance() override;

				bool _CheckPhysicalDeviceProperties(VkPhysicalDevice physical_device, uint32_t &selected_graphics_queue_family_index, uint32_t &selected_present_queue_family_index);

				VkInstance mInstance;
			};
		}
	}
}
