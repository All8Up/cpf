//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iRenderPass.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iImage;

		struct FrameBufferDesc
		{
			iRenderPass* mpRenderPass;
			int32_t mAttachmentCount;
			iImage** mpAttachments;	// TODO: Vulkan expects image views, not images.  D3D12 seems to need images though.
			int32_t mWidth;
			int32_t mHeight;
			int32_t mLayers; // TODO: Something in Vulkan I'm ignoring at the moment.
		};
	}
}
