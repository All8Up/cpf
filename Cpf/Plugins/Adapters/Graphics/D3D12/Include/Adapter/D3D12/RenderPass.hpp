//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Graphics/iRenderPass.hpp"
#include "CPF/Graphics/AttachmentDesc.hpp"
#include "CPF/Graphics/DependencyDesc.hpp"
#include "CPF/Graphics/PipelineBindPoint.hpp"
#include "CPF/Graphics/SubPassDesc.hpp"
#include "Vector.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace Graphics
	{
		struct RenderPassDesc;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr GOM::ClassID kRenderPassCID = GOM::ClassID("Adapter::D3D12::RenderPass"_crc64);

			class RenderPass : public tRefCounted<Graphics::iRenderPass>
			{
			public:
				RenderPass(Plugin::iRegistry*, GOM::iUnknown*) {}

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				GOM::Result CPF_STDCALL Initialize(const Graphics::RenderPassDesc* desc);

				using AttachmentRefVector = Vector<Graphics::AttachmentRef>;
				struct SubPassStorage
				{
					Graphics::PipelineBindPoint mBindPoint;
					AttachmentRefVector mInputAttachments;
					AttachmentRefVector mColorAttachments;
					AttachmentRefVector mResolveAttachments;
					Graphics::AttachmentRef mDepthStencilAttachment;
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
