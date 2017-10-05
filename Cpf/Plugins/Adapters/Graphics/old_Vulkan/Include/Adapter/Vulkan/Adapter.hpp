//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iAdapter.hpp"
#include "Graphics/iInstance.hpp"
#include "VulkanUtils.hpp"

namespace Cpf
{
	namespace Adapters
	{
		namespace Vulkan
		{
			class Adapter : public tRefCounted<Graphics::iAdapter>
			{
			public:
				// TODO: Enumerate attached outputs (monitors).
				// TODO: Enumerate video resolutions for outputs.
				Adapter(Graphics::iInstance* inst, VkPhysicalDevice dev) : mpInstance(inst), mPhysicalDevice(dev) {}
				~Adapter() override;
				bool IsSoftware() override;

				Graphics::iInstance* GetInstance() const { return mpInstance; }

			private:
				Graphics::iInstance* mpInstance;
				VkPhysicalDevice mPhysicalDevice;
			};
		}
	}
}
