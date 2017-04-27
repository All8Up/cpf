//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/FrameBuffer.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

FrameBuffer::FrameBuffer(COM::iUnknown*)
	: mFrameBuffer{ 0 }
{}

FrameBuffer::~FrameBuffer()
{
	SafeRelease(mFrameBuffer.mpRenderPass);
}


COM::Result CPF_STDCALL FrameBuffer::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case Graphics::iFrameBuffer::kIID.GetID():
			*outIface = static_cast<iFrameBuffer*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL FrameBuffer::Initialize(const Graphics::FrameBufferDesc* desc)
{
	if (desc)
	{
		// Copy the frame buffer data.
		mFrameBuffer = *desc;
		mFrameBuffer.mpRenderPass->AddRef();

		// Copy the attachments.  NOTE: Takes a ref count.
		mAttachments.resize(desc->mAttachmentCount);
		for (int i = 0; i < desc->mAttachmentCount; ++i)
			mAttachments[i].Assign(desc->mpAttachments[i]);

		// Make sure we don't reference the old pointer.
		mFrameBuffer.mpAttachments = nullptr;

		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
