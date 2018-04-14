//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iCommandPool.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Vulkan
	{
		class Device;

		class CommandPool : public GOM::tUnknown <Graphics::iCommandPool>
		{
		public:
			GOM::Result Initialize(Device* device);
			VkCommandPool GetVkCommandPool() const { return mCommandPool; }

			void CPF_STDCALL Reset() override;

		private:
			Device* mpDevice;
			VkCommandPool mCommandPool;
		};
	}
}
