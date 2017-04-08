//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iStage.hpp"
#include "Graphics/RenderPassDesc.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/iRenderPass.hpp"
#include "Graphics/FrameBufferDesc.hpp"
#include "Graphics/iFrameBuffer.hpp"

using namespace Cpf;
using namespace Concurrency;
using namespace MultiCore;

COM::Result RenderSystem::Install(Plugin::iRegistry* regy)
{
	class RenderSystemClass : public tRefCounted<Plugin::iClassInstance>
	{
	public:
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
		COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
		{
			if (outIface)
			{
				*outIface = new RenderSystem();
				return *outIface ? COM::kOK : COM::kOutOfMemory;
			}
			return COM::kInvalidParameter;
		}
	};
	return regy->Install(kRenderSystemCID, new RenderSystemClass());
}

COM::Result RenderSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kRenderSystemCID);
}

RenderSystem::RenderSystem()
{
	// TODO: Testing for render pass setup.
	Graphics::AttachmentDesc attachments[2] = {};

	//////////////////////////////////////////////////////////////////////////
	// Color buffer.
	attachments[0].mFlags = 0;
	attachments[0].mFormat = Graphics::Format::eRGBA8un;
	attachments[0].mSamples = Graphics::SampleDesc{ 1, 0 };
	attachments[0].mLoadOp = Graphics::LoadOp::eClear;
	attachments[0].mStoreOp = Graphics::StoreOp::eStore;
	attachments[0].mStencilLoadOp = Graphics::LoadOp::eDontCare;
	attachments[0].mStencilStoreOp = Graphics::StoreOp::eDontCare;
	// TODO: Figure out what makes the most sense.
	attachments[0].mStartState = Graphics::ResourceState::ePresent;
	attachments[0].mFinalState = Graphics::ResourceState::ePresent;

	///
	Graphics::AttachmentRef colorAttachment = {};
	colorAttachment.mIndex = 0;
	colorAttachment.mState = Graphics::ResourceState::eRenderTarget;

	//////////////////////////////////////////////////////////////////////////
	// Depth buffer.
	attachments[1].mFlags = 0;
	attachments[1].mFormat = Graphics::Format::eD32f;
	attachments[1].mSamples = Graphics::SampleDesc{ 1, 0 };
	attachments[1].mLoadOp = Graphics::LoadOp::eClear;
	attachments[1].mStoreOp = Graphics::StoreOp::eStore;
	attachments[1].mStencilLoadOp = Graphics::LoadOp::eLoad;
	attachments[1].mStencilStoreOp = Graphics::StoreOp::eStore;
	// TODO: Figure out what makes the most sense.
	attachments[1].mStartState = Graphics::ResourceState::ePresent;
	attachments[1].mFinalState = Graphics::ResourceState::ePresent;

	///
	Graphics::AttachmentRef depthAttachment = {};
	depthAttachment.mIndex = 1;
	depthAttachment.mState = Graphics::ResourceState::eDepthWrite;

	//////////////////////////////////////////////////////////////////////////
	Graphics::SubPassDesc subPass = {};
	subPass.mBindPoint = Graphics::PipelineBindPoint::eGraphic;
	// No inputs.
	subPass.mInputCount = 0;
	subPass.mpInputAttachments = nullptr;
	// 1 color output.
	subPass.mColorCount = 1;
	subPass.mpColorAttachments = &colorAttachment;
	// No resolves.
	subPass.mResolveCount = 0;
	subPass.mpResolveAttachments = nullptr;
	// 1 depth buffer.
	subPass.mDepthStencilCount = 1;
	subPass.mpDepthStencilAttachments = &depthAttachment;
	// No preservation.
	subPass.mPreserveCount = 0;
	subPass.mpPreserveAttachments = nullptr;

	//////////////////////////////////////////////////////////////////////////
	Graphics::RenderPassDesc renderPassDesc;
	renderPassDesc.mAttachmentCount = 2;
	renderPassDesc.mpAttachments = attachments;
	renderPassDesc.mSubPassCount = 1;
	renderPassDesc.mpSubPasses = &subPass;
	renderPassDesc.mDependencyCount = 0;
	renderPassDesc.mpDependencies = nullptr;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<Graphics::iRenderPass> renderPass;
//	mpDevice->CreateRenderPass(&renderPassDesc, renderPass.AsTypePP());

	//////////////////////////////////////////////////////////////////////////
	Graphics::FrameBufferDesc frameBufferDesc;
	frameBufferDesc.mpRenderPass = renderPass;
	frameBufferDesc.mAttachmentCount = 2;
	Graphics::iImageView* views[2] = {};
	frameBufferDesc.mpAttachments = views;
	frameBufferDesc.mWidth = 1024;
	frameBufferDesc.mHeight = 768;
	frameBufferDesc.mLayers = 1;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<Graphics::iFrameBuffer> frameBuffer;
//	mpDevice->CreateFrameBuffer(&frameBufferDesc, frameBuffer.AsTypePP());
}

RenderSystem::~RenderSystem()
{}

void RenderSystem::_AllocateBuffers()
{
	/*
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpDevice->CreateCommandPool(mpPreCommandPool[i].AsTypePP());
		mpDevice->CreateCommandPool(mpPostCommandPool[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPreCommandPool[i], mpPreCommandBuffer[i].AsTypePP());
		mpDevice->CreateCommandBuffer(mpPostCommandPool[i], mpPostCommandBuffer[i].AsTypePP());
	}
	*/
}

void RenderSystem::_BeginFrame(ThreadContext& tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_BeginFrame(tc);
}
void RenderSystem::_Clear(ThreadContext& tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_ClearBuffers(tc);
}
void RenderSystem::_Draw(ThreadContext& tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_Draw(tc);
}
void RenderSystem::_DebugUI(ThreadContext& tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_DebugUI(tc);
}
void RenderSystem::_PreparePresent(ThreadContext& tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_PreparePresent(tc);
}
void RenderSystem::_EndFrame(Concurrency::ThreadContext& tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_EndFrame(tc);
}


//////////////////////////////////////////////////////////////////////////
COM::Result CPF_STDCALL RenderSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case RenderSystem::kIID.GetID():
			*outIface = static_cast<RenderSystem*>(this);
			break;

		default:
			return COM::kNotImplemented;
		}

		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL RenderSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc)
{
	(void)rgy;
	if (name)
	{
		const RenderSystem::Desc* theDesc = static_cast<const RenderSystem::Desc*>(desc);
		mpApp = theDesc->mpApplication;
		mCurrentBackBuffer = 0;
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(nullptr, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (COM::Succeeded(result))
		{
			// Build the stages and set the update function for each.
			// NOTE: While there are 6 stages which must operate in order, there will only
			// be two required barrier groups since the only thing required is that they
			// run in order which is accomplished via series of eLast types.
			IntrusivePtr<MultiCore::iSingleUpdateStage> beginFrame;
			rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, beginFrame.AsVoidPP());
			beginFrame->Initialize(this, kBeginFrame.GetString());
			beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, MultiCore::BlockOpcode::eFirst);

			// Paired in a group ^
			IntrusivePtr<MultiCore::iSingleUpdateStage> clearBuffers;
			rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, clearBuffers.AsVoidPP());
			clearBuffers->Initialize(this, kClearBuffers.GetString());
			clearBuffers->SetUpdate(&RenderSystem::_Clear, this, MultiCore::BlockOpcode::eLast);

			IntrusivePtr<MultiCore::iSingleUpdateStage> drawInstances;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, drawInstances.AsVoidPP());
			drawInstances->Initialize(this, kDrawInstances.GetString());
			drawInstances->SetUpdate(&RenderSystem::_Draw, this, MultiCore::BlockOpcode::eLast);

			IntrusivePtr<MultiCore::iSingleUpdateStage> debugUI;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, debugUI.AsVoidPP());
			debugUI->Initialize(this, kDebugUI.GetString());
			debugUI->SetUpdate(&RenderSystem::_DebugUI, this, MultiCore::BlockOpcode::eLast);

			IntrusivePtr<MultiCore::iSingleUpdateStage> preparePresent;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, preparePresent.AsVoidPP());
			preparePresent->Initialize(this, kPreparePresent.GetString());
			preparePresent->SetUpdate(&RenderSystem::_PreparePresent, this, MultiCore::BlockOpcode::eLast);

			IntrusivePtr<MultiCore::iSingleUpdateStage> endFrame;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, endFrame.AsVoidPP());
			endFrame->Initialize(this, kEndFrame.GetString());
			endFrame->SetUpdate(&RenderSystem::_EndFrame, this, MultiCore::BlockOpcode::eLast);

			// Add the stages.
			AddStage(beginFrame);
			AddStage(clearBuffers);
			AddStage(drawInstances);
			AddStage(debugUI);
			AddStage(preparePresent);
			AddStage(endFrame);

			// Add the default set of dependencies.
			AddDependency({
				{ GetID(), clearBuffers->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), beginFrame->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), drawInstances->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), clearBuffers->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), debugUI->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), drawInstances->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), preparePresent->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), debugUI->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), endFrame->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), preparePresent->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});

			_AllocateBuffers();

			return COM::kOK;
		}
		return result;
	}
	return COM::kInvalidParameter;
}

SystemID CPF_STDCALL RenderSystem::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL RenderSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL RenderSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

COM::Result CPF_STDCALL RenderSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL RenderSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL RenderSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL RenderSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}
