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
			int32_t mAttachmentCount;
			AttachmentRef* mpColorAttachments;
			AttachmentRef* mpResolveAttachments;
			AttachmentRef* mpDepthStencilAttachment;
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
