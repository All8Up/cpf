//////////////////////////////////////////////////////////////////////////
#pragma once
#include "VulkanUtils.hpp"
#include "Graphics/iInstance.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		struct iDevice;
		struct iAdapter;
		struct iSwapChain;
		struct SwapChainDesc;
	}
	namespace Adapters
	{
		namespace Vulkan
		{
			//////////////////////////////////////////////////////////////////////////
			class Instance : public tRefCounted<Graphics::iInstance>
			{
			public:
				static void* Create();

				COM::Result CPF_STDCALL EnumerateAdapters(int& count, Graphics::iAdapter** adapters) override;
				COM::Result CPF_STDCALL CreateDevice(Graphics::iAdapter*, Graphics::iDevice**) override;

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
