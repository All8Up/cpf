//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iRenderPass.hpp"
#include "CPF/Platform/Graphics/AttachmentDesc.hpp"
#include "CPF/Platform/Graphics/DependencyDesc.hpp"
#include "CPF/Platform/Graphics/PipelineBindPoint.hpp"
#include "CPF/Platform/Graphics/SubPassDesc.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/GOM/tUnknown.hpp"

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

	namespace Driver
	{
		namespace D3D12
		{
			static constexpr GOM::ClassID kRenderPassCID = GOM::ClassID("Adapter::D3D12::RenderPass"_crc64);

			class RenderPass final : public GOM::tUnknown<Graphics::iRenderPass>
			{
			public:
				RenderPass(Plugin::iRegistry*, GOM::iUnknown*) {}

				GOM::Result CPF_STDCALL Initialize(const Graphics::RenderPassDesc* desc);

				using AttachmentRefVector = STD::Vector<Graphics::AttachmentRef>;
				struct SubPassStorage
				{
					Graphics::PipelineBindPoint mBindPoint;
					AttachmentRefVector mInputAttachments;
					AttachmentRefVector mColorAttachments;
					AttachmentRefVector mResolveAttachments;
					Graphics::AttachmentRef mDepthStencilAttachment;
					AttachmentRefVector mPreserveAttachments;
				};
				using SubPassVector = STD::Vector<SubPassStorage>;
				using AttachmentDescVector = STD::Vector<Graphics::AttachmentDesc>;
				using DependencyDescVector = STD::Vector<Graphics::DependencyDesc>;
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
