//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iFence.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Vulkan
	{
		class Device;

		class Fence : public GOM::tUnknown <Graphics::iFence>
		{
		public:
			// Implementation.
			GOM::Result Initialize(Device* device, bool signaled);
			VkFence GetVkFence() const { return mFence; }

			// iFence overrides.
			Graphics::FenceStatus CPF_STDCALL GetStatus() const override;
			void CPF_STDCALL Reset() override;
			Graphics::FenceStatus CPF_STDCALL Wait() const override;

		private:
			Device* mpDevice;
			VkFence mFence;
		};
	}
}
