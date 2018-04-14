//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vulkan.hpp"
#include "CPF/Platform/Graphics/iInstance.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Std/Vector.hpp"

namespace CPF
{
	namespace Vulkan
	{
		static constexpr GOM::ClassID kVulkanInstanceCID = GOM::ClassID("Vulkan::Instance"_crc64);
		class Instance final : public GOM::tUnknown<Graphics::iInstance>
		{
		public:
			// Construction/Destruction.
			Instance(Plugin::iRegistry*, iUnknown* outer);
			virtual ~Instance();

			// Overrides for iInstance.
			GOM::Result CPF_STDCALL Initialize(const Graphics::InstanceDesc* desc) override;
			GOM::Result CPF_STDCALL EnumerateAdapters(int* count, Graphics::iAdapter** adapters) override;
			GOM::Result CPF_STDCALL CreateDevice(Graphics::iAdapter* adapter, Graphics::iDevice** device) override;

			//
			VkInstance GetInstance() const { return mInstance; }

		private:
			STD::Vector<VkLayerProperties> EnumerateInstanceLayers() const;
			STD::Vector<VkExtensionProperties> EnumerateInstanceExtensions() const;
			void EnableLayer(const char* layer, const STD::Vector<VkLayerProperties>& available, STD::Vector<const char*>& required) const;

			Plugin::iRegistry* mpRegistry;
			VkInstance mInstance;
		};
	}
}
