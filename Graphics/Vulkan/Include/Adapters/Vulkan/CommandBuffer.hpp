//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver/iCommandBuffer.hpp"
#include "IntrusivePtr.hpp"
#include "VulkanUtils.hpp"


namespace Cpf
{
	namespace Graphics
	{
		namespace Driver
		{
			class iDevice;
			class iSwapChain;
			class iCommandPool;
		}
	}

	namespace Adapters
	{
		namespace Vulkan
		{
			class Device;
			class CommandPool;

			class CommandBuffer : public tRefCounted<Graphics::Driver::iCommandBuffer>
			{
			public:
				CommandBuffer(Graphics::Driver::iDevice*, Graphics::Driver::iCommandPool*);
				~CommandBuffer() override;

				void Begin() override;
				void End() override;
				void Reset(Graphics::Driver::iCommandPool*) override;

				// TODO: This is temporary porting work.
				void ToBePorted(Graphics::Driver::iDevice*, Graphics::Driver::iSwapChain*);

			private:
				Device* mpDevice;
				CommandPool* mpCommandPool;

				VkCommandBuffer mpCommandBuffer;
			};
		}
	}
}
