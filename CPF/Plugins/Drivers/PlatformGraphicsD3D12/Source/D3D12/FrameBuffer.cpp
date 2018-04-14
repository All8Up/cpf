//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/FrameBuffer.hpp"
#include "CPF/Platform/Graphics/iRenderPass.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Driver;
using namespace D3D12;

FrameBuffer::FrameBuffer(Plugin::iRegistry*, GOM::iUnknown*)
	: mFrameBuffer{ 0 }
{}

FrameBuffer::~FrameBuffer()
{
	SafeRelease(mFrameBuffer.mpRenderPass);
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
