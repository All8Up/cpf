//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/AttachmentDesc.hpp"
#include "Graphics/PipelineBindPoint.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct SubPassDesc
		{
			PipelineBindPoint mBindPoint;
			int32_t mInputCount;
			AttachmentRef* mpInputAttachments;
			int32_t mColorCount;
			AttachmentRef* mpColorAttachments;
			int32_t mResolveCount;
			AttachmentRef* mpResolveAttachments;
			int32_t mDepthStencilCount;
			AttachmentRef* mpDepthStencilAttachments;
			int32_t mPreserveCount;
			AttachmentRef* mpPreserveAttachments;
		};

		struct DependencyDesc
		{
			int32_t mSubPassSource;
			int32_t mSubPassDependant;
		};
	}
}
