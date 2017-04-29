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

				using AttachmentRefVector = Vector<Graphics::AttachmentRef>;
				struct SubPassStorage
				{
					Graphics::PipelineBindPoint mBindPoint;
					AttachmentRefVector mInputAttachments;
					AttachmentRefVector mColorAttachments;
					AttachmentRefVector mResolveAttachments;
					AttachmentRefVector mDepthStencilAttachments;
					AttachmentRefVector mPreserveAttachments;
				};
				using SubPassVector = Vector<SubPassStorage>;
				using AttachmentDescVector = Vector<Graphics::AttachmentDesc>;
				using DependencyDescVector = Vector<Graphics::DependencyDesc>;
				struct RenderPassStorage
				{
					AttachmentDescVector mAttachments;
					SubPassVector mSubPasses;
					DependencyDescVector mDependencies;
				};

				const RenderPassStorage& GetRenderPassDesc() const { return mRenderPass; }

			private:
				RenderPassStorage mRenderPass;
			};
		}
	}
}
