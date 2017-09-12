//////////////////////////////////////////////////////////////////////////
#include "Graphics/iFrameBuffer.hpp"
#include "Graphics/FrameBufferDesc.hpp"
#include "Graphics/iImageView.hpp"
#include "Vector.hpp"

namespace CPF
{
	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr GOM::ClassID kFrameBufferCID = GOM::ClassID("Adapter::D3D12::FrameBuffer"_crc64);

			class FrameBuffer : public tRefCounted<Graphics::iFrameBuffer>
			{
			public:
				FrameBuffer(GOM::iUnknown*);
				virtual ~FrameBuffer();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				GOM::Result CPF_STDCALL Initialize(const Graphics::FrameBufferDesc* desc);

				using ImageVector = Vector<Graphics::ImageAndView>;
				const ImageVector& GetImages() const { return mAttachments; }
				const Graphics::FrameBufferDesc& GetFrameBufferDesc() const { return mFrameBuffer; }

			private:
				ImageVector mAttachments;
				Graphics::FrameBufferDesc mFrameBuffer;
			};
		}
	}
}
