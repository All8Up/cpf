//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iCommandPool.hpp"
#include "IntrusivePtr.hpp"
#include "VulkanUtils.hpp"

namespace Cpf
{
	namespace Adapters
	{
		namespace Vulkan
		{
			class Device;

			class CommandPool : public tRefCounted<Graphics::Driver::iCommandPool>
			{
			public:
				CommandPool(Device* device);
				~CommandPool() override;

				void Reset() override;

				VkCommandPool GetPool() { return mpCommandPool; }

			private:
				Device* mpDevice;
				VkCommandPool mpCommandPool;
			};
		}
	}
}
