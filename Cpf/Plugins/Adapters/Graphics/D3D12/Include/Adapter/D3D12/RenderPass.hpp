//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iRenderPass.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct RenderPassDesc;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr COM::ClassID kRenderPassCID = COM::ClassID("Adapter::D3D12::RenderPass"_crc64);

			class RenderPass : public tRefCounted<Graphics::iRenderPass>
			{
			public:
				RenderPass(COM::iUnknown*) {}

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				COM::Result CPF_STDCALL Initialize(const Graphics::RenderPassDesc* desc);

			private:
				Vector<Graphics::SubPassDesc> mSubPasses;
				Vector<Graphics::AttachmentDesc> mAttachments;
				Vector<Vector<Graphics::AttachmentRef>> mAttachmentRefs;
			};
		}
	}
}
