//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/RenderPass.hpp"
#include "Graphics/RenderPassDesc.hpp"
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

		// Copy subpasses.
		mSubPasses.resize(desc->mSubPassCount);
		MemCpy(mSubPasses.data(), desc->mpSubPasses, sizeof(Graphics::SubPassDesc)*desc->mSubPassCount);

		// Copy the attachment refs and perform fixup.
		mAttachmentRefs.resize(desc->mSubPassCount);
		for (int i=0; i<desc->mSubPassCount; ++i)
		{
			Graphics::SubPassDesc& subPass = mSubPasses[i];
			mAttachmentRefs[i].resize(
				subPass.mInputCount +
				subPass.mColorCount +
				subPass.mResolveCount +
				subPass.mDepthStencilCount +
				subPass.mPreserveCount
			);
			Vector<Graphics::AttachmentRef>& refs = mAttachmentRefs[i];

			// Copy input refs and point to the new data.
			for (int j = 0; j < subPass.mInputCount; ++j)
				refs[j] = subPass.mpInputAttachments[j];
			subPass.mpInputAttachments = refs.data();
			int32_t offset = subPass.mInputCount;

			// Copy color refs and point to the new data.
			for (int j = 0; j < subPass.mColorCount; ++j)
				refs[j+offset] = subPass.mpColorAttachments[j];
			subPass.mpColorAttachments = refs.data() + offset;
			offset += subPass.mColorCount;

			// Copy resolve refs and point to the new data.
			for (int j = 0; j < subPass.mResolveCount; ++j)
				refs[j + offset] = subPass.mpResolveAttachments[j];
			subPass.mpResolveAttachments = refs.data() + offset;
			offset += subPass.mResolveCount;

			// Copy depth refs and point to the new data.
			for (int j = 0; j < subPass.mDepthStencilCount; ++j)
				refs[j + offset] = subPass.mpDepthStencilAttachments[j];
			subPass.mpDepthStencilAttachments = refs.data() + offset;
			offset += subPass.mDepthStencilCount;

			// Copy preserve refs and point to the new data.
			for (int j = 0; j < subPass.mPreserveCount; ++j)
				refs[j + offset] = subPass.mpPreserveAttachments[j];
			subPass.mpPreserveAttachments = refs.data() + offset;
		}

		// Copy attachments.
		mAttachments.resize(desc->mAttachmentCount);
		MemCpy(mAttachments.data(), desc->mpAttachments, sizeof(Graphics::AttachmentDesc)*desc->mAttachmentCount);

		return COM::kOK;
	}

	return COM::kInvalidParameter;
}
