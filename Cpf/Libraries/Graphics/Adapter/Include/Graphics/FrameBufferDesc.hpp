//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iRenderPass.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iImage;
		struct iImageView;
		struct ImageAndView
		{
			iImage* mpImage;
			iImageView* mpImageView;
		};

		struct FrameBufferDesc
		{
			iRenderPass* mpRenderPass;
			int32_t mAttachmentCount;
			ImageAndView* mpAttachments;	// TODO: Vulkan expects image views, not images.  D3D12 seems to need images though.
			int32_t mWidth;
			int32_t mHeight;
			int32_t mLayers; // TODO: Something in Vulkan I'm ignoring at the moment.
		};
	}
}
