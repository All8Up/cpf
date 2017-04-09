//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iRenderPass.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iImageView;

		struct FrameBufferDesc
		{
			iRenderPass* mpRenderPass;
			int32_t mAttachmentCount;
			iImageView** mpAttachments;
			int32_t mWidth;
			int32_t mHeight;
			int32_t mLayers; // TODO: ?? What is the usage of this?
		};
	}
}
