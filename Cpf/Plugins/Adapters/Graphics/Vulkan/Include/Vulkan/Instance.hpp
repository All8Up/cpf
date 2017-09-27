//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vulkan.hpp"
#include "Graphics/iInstance.hpp"

namespace CPF
{
	namespace Vulkan
	{
		static constexpr GOM::ClassID kVulkanInstanceCID = GOM::ClassID("Vulkan::Instance"_crc64);
		class Instance : public tRefCounted<Graphics::iInstance>
		{
		public:
			// Construction/Destruction.
			Instance(iUnknown* outer);
			virtual ~Instance();

			// Overrides for iUnknown.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			// Overrides for iInstance.
			GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* registry) override;
			GOM::Result CPF_STDCALL EnumerateAdapters(int* count, Graphics::iAdapter** adapters) override;
			GOM::Result CPF_STDCALL CreateDevice(Graphics::iAdapter* adapter, Graphics::iDevice** device) override;

		private:
			VkInstance mInstance;
		};
	}
}
