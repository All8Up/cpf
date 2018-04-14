//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/RenderPass.hpp"
#include "CPF/Platform/Graphics/RenderPassDesc.hpp"
#include "CPF/Platform/Graphics/ResourceState.hpp"
#include "CPF/Std/Memory.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace CSTD;
using namespace Driver;
using namespace D3D12;

GOM::Result CPF_STDCALL RenderPass::Initialize(const Graphics::RenderPassDesc* desc)
{
	if (desc)
	{
		// TODO: Dependencies not implemented yet.
		CPF_ASSERT(desc->mDependencyCount == 0);
		CPF_ASSERT(desc->mpDependencies == nullptr);

		// Copy the attachments.
		mRenderPass.mAttachments.resize(desc->mAttachmentCount);
		mRenderPass.mAttachments.assign(desc->mpAttachments, desc->mpAttachments + desc->mAttachmentCount);

		// Copy sub passes.
		mRenderPass.mSubPasses.resize(desc->mSubPassCount);
		for (int i = 0; i < desc->mSubPassCount; ++i)
		{
			auto& source = desc->mpSubPasses[i];
			auto& target = mRenderPass.mSubPasses[i];

			target.mBindPoint = desc->mpSubPasses[i].mBindPoint;
			target.mInputAttachments.assign(source.mpInputAttachments, source.mpInputAttachments + source.mInputCount);
			target.mColorAttachments.assign(source.mpColorAttachments, source.mpColorAttachments + source.mAttachmentCount);
			if (source.mpResolveAttachments)
				target.mResolveAttachments.assign(source.mpResolveAttachments, source.mpResolveAttachments + source.mAttachmentCount);
			if (source.mpDepthStencilAttachment)
				target.mDepthStencilAttachment = *source.mpDepthStencilAttachment;
			else
				target.mDepthStencilAttachment = { Graphics::kInvalidAttachment, Graphics::ResourceState::eCommon };
		}

		return GOM::kOK;
	}

	return GOM::kInvalidParameter;
}
