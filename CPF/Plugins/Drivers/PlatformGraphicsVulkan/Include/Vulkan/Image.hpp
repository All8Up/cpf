//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iImage.hpp"
#include "CPF/Platform/Graphics/HeapType.hpp"
#include "CPF/Platform/Graphics/ImageDesc.hpp"
#include "CPF/Platform/Graphics/ClearValue.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Vulkan
	{
		class Device;

		class Image final : public GOM::tUnknown<Graphics::iImage>
		{
		public:
			//
			bool CPF_STDCALL Map(void** buffer, const Graphics::Range* range) override;
			void CPF_STDCALL Unmap(const Graphics::Range* range) override;

			//
			GOM::Result CPF_STDCALL GetDesc(Graphics::ImageDesc* desc) const override;

			//
			GOM::Result Initialize(VkImage image);
			GOM::Result Create2D(Device*, Graphics::HeapType heap, const Graphics::ClearValue* clearValue, const Graphics::ImageDesc* desc);

			VkImage GetVkImage() const { return mImage; }

		private:
			static uint32_t FindMemoryType(Device* device, uint32_t typeFilter, VkMemoryPropertyFlags properties);

			Graphics::ImageDesc mDesc;
			VkImage mImage;
			VkDeviceMemory mDeviceMemory;
		};
	}
}