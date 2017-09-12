//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/SubPassDesc.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct RenderPassDesc
		{
			int32_t mAttachmentCount;
			AttachmentDesc* mpAttachments;
			int32_t mSubPassCount;
			SubPassDesc* mpSubPasses;
			int32_t mDependencyCount;
			DependencyDesc* mpDependencies;
		};
	}
}
