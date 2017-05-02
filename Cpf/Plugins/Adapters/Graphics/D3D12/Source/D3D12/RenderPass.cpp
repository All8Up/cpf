//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/RenderPass.hpp"
#include "Graphics/RenderPassDesc.hpp"
#include "Graphics/ResourceState.hpp"
#include "Std/Memory.hpp"

using namespace Cpf;
using namespace Std;
using namespace Adapter;
using namespace D3D12;

COM::Result CPF_STDCALL RenderPass::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case Graphics::iRenderPass::kIID.GetID():
			*outIface = static_cast<iRenderPass*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL RenderPass::Initialize(const Graphics::RenderPassDesc* desc)
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

		return COM::kOK;
	}

	return COM::kInvalidParameter;
}
