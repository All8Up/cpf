//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Graphics/ClearValue.hpp"
#include "Math/Rectangle.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iRenderPass;
		class iFrameBuffer;

		struct RenderPassBeginDesc
		{
			iRenderPass* mpRenderPass;
			iFrameBuffer* mpFrameBuffer;
			Math::Rectanglei mClipRect;
			int32_t mClearValueCount;
			const ClearValue* mpClearValues;
		};
	}
}
