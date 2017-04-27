//////////////////////////////////////////////////////////////////////////
#include "Graphics/iFrameBuffer.hpp"
#include "Graphics/FrameBufferDesc.hpp"
#include "Graphics/iImageView.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr COM::ClassID kFrameBufferCID = COM::ClassID("Adapter::D3D12::FrameBuffer"_crc64);

			class FrameBuffer : public tRefCounted<Graphics::iFrameBuffer>
			{
			public:
				FrameBuffer(COM::iUnknown*);
				virtual ~FrameBuffer();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				COM::Result CPF_STDCALL Initialize(const Graphics::FrameBufferDesc* desc);

			private:
				Vector<IntrusivePtr<Graphics::iImageView>> mAttachments;
				Graphics::FrameBufferDesc mFrameBuffer;
			};
		}
	}
}
