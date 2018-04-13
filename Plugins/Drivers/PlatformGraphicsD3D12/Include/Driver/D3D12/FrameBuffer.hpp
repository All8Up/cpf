//////////////////////////////////////////////////////////////////////////
#include "CPF/Platform/Graphics/iFrameBuffer.hpp"
#include "CPF/Platform/Graphics/FrameBufferDesc.hpp"
#include "CPF/Platform/Graphics/iImageView.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace Driver
	{
		namespace D3D12
		{
			static constexpr GOM::ClassID kFrameBufferCID = GOM::ClassID("Adapter::D3D12::FrameBuffer"_crc64);

			class FrameBuffer final : public GOM::tUnknown<Graphics::iFrameBuffer>
			{
			public:
				FrameBuffer(Plugin::iRegistry*, GOM::iUnknown*);
				virtual ~FrameBuffer();

				GOM::Result CPF_STDCALL Initialize(const Graphics::FrameBufferDesc* desc);

				using ImageVector = STD::Vector<Graphics::ImageAndView>;
				const ImageVector& GetImages() const { return mAttachments; }
				const Graphics::FrameBufferDesc& GetFrameBufferDesc() const { return mFrameBuffer; }

			private:
				ImageVector mAttachments;
				Graphics::FrameBufferDesc mFrameBuffer;
			};
		}
	}
}
