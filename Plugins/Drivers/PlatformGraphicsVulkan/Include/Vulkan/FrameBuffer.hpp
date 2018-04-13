//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iFrameBuffer.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "Vulkan.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct FrameBufferDesc;
	}

	namespace Vulkan
	{
		class Device;

		class FrameBuffer : public GOM::tUnknown <Graphics::iFrameBuffer>
		{
		public:
			GOM::Result Initialize(Device* device, const Graphics::FrameBufferDesc* desc);

			VkFramebuffer GetVkFrameBuffer() const { return mFrameBuffer; }

		private:
			VkFramebuffer mFrameBuffer;
		};
	}
}
