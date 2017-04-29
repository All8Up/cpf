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

				using SubPassVector = Vector<Graphics::SubPassDesc>;
				using AttachmentVector = Vector<Graphics::AttachmentDesc>;
				using AttachmentRefVector = Vector<Graphics::AttachmentRef>;

				int32_t GetSubPassCount() const { return int32_t(mSubPasses.size()); }
				const SubPassVector& GetSubPasses() const { return mSubPasses; }
				const AttachmentVector& GetAttachments() const { return mAttachments; }
				const AttachmentRefVector& GetAttachments(int32_t index) const { return mAttachmentRefs[index]; }

			private:
				SubPassVector mSubPasses;
				AttachmentVector mAttachments;
				Vector<AttachmentRefVector> mAttachmentRefs;
			};
		}
	}
}
