//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/FrameBuffer.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

FrameBuffer::FrameBuffer(GOM::iBase*)
	: mFrameBuffer{ 0 }
{}

FrameBuffer::~FrameBuffer()
{
	SafeRelease(mFrameBuffer.mpRenderPass);
}


GOM::Result CPF_STDCALL FrameBuffer::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;
		case Graphics::iFrameBuffer::kIID.GetID():
			*outIface = static_cast<iFrameBuffer*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL FrameBuffer::Initialize(const Graphics::FrameBufferDesc* desc)
{
	if (desc)
	{
		// Copy the frame buffer data.
		mFrameBuffer = *desc;
		if (mFrameBuffer.mpRenderPass)
		{
			mFrameBuffer.mpRenderPass->AddRef();

			// Copy the attachments.  NOTE: Takes a ref count.
			mAttachments.resize(desc->mAttachmentCount);
			for (int i = 0; i < desc->mAttachmentCount; ++i)
				mAttachments[i] = desc->mpAttachments[i];

			// Make sure we don't reference the old pointer.
			mFrameBuffer.mpAttachments = nullptr;

			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}
