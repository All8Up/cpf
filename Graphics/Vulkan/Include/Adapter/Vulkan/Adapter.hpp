//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iAdapter.hpp"
#include "Graphics/Driver/iInstance.hpp"
#include "VulkanUtils.hpp"

namespace Cpf
{
	namespace Adapters
	{
		namespace Vulkan
		{
			class Adapter : public tRefCounted<Graphics::Driver::iAdapter>
			{
			public:
				// TODO: Enumerate attached outputs (monitors).
				// TODO: Enumerate video resolutions for outputs.
				Adapter(Graphics::Driver::iInstance* inst, VkPhysicalDevice dev) : mpInstance(inst), mPhysicalDevice(dev) {}
				~Adapter() override;
				bool IsSoftware() override;

				Graphics::Driver::iInstance* GetInstance() const { return mpInstance; }

			private:
				Graphics::Driver::iInstance* mpInstance;
				VkPhysicalDevice mPhysicalDevice;
			};
		}
	}
}
