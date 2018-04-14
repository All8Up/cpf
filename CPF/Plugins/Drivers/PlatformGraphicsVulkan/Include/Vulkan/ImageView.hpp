//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iImageView.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iImage;
	}

	namespace Vulkan
	{
		class Device;

		class ImageView : public GOM::tUnknown<Graphics::iImageView>
		{
		public:

			GOM::Result Initialize(Device* device, Graphics::iImage* image, VkFormat format, bool depth = false);
			VkImageView GetVkImageView() const { return mImageView; }

		private:
			VkImageView mImageView;
		};
	}
}
