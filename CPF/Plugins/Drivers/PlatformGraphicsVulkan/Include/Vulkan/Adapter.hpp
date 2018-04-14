//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iAdapter.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Std/Vector.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace Vulkan
	{
		static constexpr GOM::ClassID kVulkanAdapterCID = GOM::ClassID("Vulkan::Adapter"_crc64);
		class Adapter final : public GOM::tUnknown<Graphics::iAdapter>
		{
		public:
			// Construction/Destruction.
			Adapter(Plugin::iRegistry*, iUnknown* outer);
			virtual ~Adapter();

			// Internal implementation.
			GOM::Result Initialize(VkPhysicalDevice device);
			VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }
			uint32_t GetGraphicsQueueIndex() const { return mGraphicsQueueIndex; }
			const STD::Vector<float>& GetQueuePriorities() const { return mQueuePriorities; }
			uint32_t GetQueueCount() const { return mQueueFamilyCount; }

			// Overrides from iAdapter.
			const char* CPF_STDCALL GetDescription() const override;
			size_t CPF_STDCALL GetVideoMemory() const override;
			size_t CPF_STDCALL GetSystemMemory() const override;
			size_t CPF_STDCALL GetSharedMemory() const override;

			bool CPF_STDCALL IsSoftware() const override;
			bool CPF_STDCALL IsRemote() const override;

			GOM::Result CPF_STDCALL EnumerateOutputs(int32_t* count, Graphics::iOutput**) const override;

		private:
			Plugin::iRegistry* mpRegistry;
			VkPhysicalDevice mPhysicalDevice;
			VkPhysicalDeviceProperties mPhysicalDeviceProperties;

			static constexpr uint32_t kInvalidQueueIndex = uint32_t(-1);
			uint32_t mQueueFamilyCount = 0;
			uint32_t mGraphicsQueueIndex = kInvalidQueueIndex;
			uint32_t mComputeQueueIndex = kInvalidQueueIndex;
			uint32_t mTransferQueueIndex = kInvalidQueueIndex;
			STD::Vector<float> mQueuePriorities;
		};
	}
}
