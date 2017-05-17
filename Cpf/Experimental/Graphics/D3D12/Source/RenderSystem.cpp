//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iStage.hpp"

using namespace Cpf;
using namespace Concurrency;
using namespace MultiCore;

GOM::Result RenderSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kRenderSystemCID, new Plugin::tClassInstance<RenderSystem>());
}

GOM::Result RenderSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kRenderSystemCID);
}

RenderSystem::RenderSystem(GOM::iUnknown*)
	: mpApp(nullptr)
	, mCurrentBackBuffer(0)
{
}

RenderSystem::~RenderSystem()
{}

void RenderSystem::_BeginFrame(const Concurrency::WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_BeginFrame(tc);
}
void RenderSystem::_Draw(const Concurrency::WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_Draw(tc);
}
void RenderSystem::_DebugUI(const Concurrency::WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_DebugUI(tc);
}
void RenderSystem::_EndFrame(const Concurrency::WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_EndFrame(tc);
}


//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL RenderSystem::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case RenderSystem::kIID.GetID():
			*outIface = static_cast<RenderSystem*>(this);
			break;

		default:
			return GOM::kNotImplemented;
		}

		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL RenderSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc)
{
	(void)rgy;
	if (name)
	{
		const RenderSystem::Desc* theDesc = static_cast<const RenderSystem::Desc*>(desc);
		mpApp = theDesc->mpApplication;
		mCurrentBackBuffer = 0;
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(this, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (GOM::Succeeded(result))
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
			IntrusivePtr<MultiCore::iSingleUpdateStage> drawInstances;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, drawInstances.AsVoidPP());
			drawInstances->Initialize(this, kDrawInstances.GetString());
			drawInstances->SetUpdate(&RenderSystem::_Draw, this, MultiCore::BlockOpcode::eLast);

			IntrusivePtr<MultiCore::iSingleUpdateStage> debugUI;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, debugUI.AsVoidPP());
			debugUI->Initialize(this, kDebugUI.GetString());
			debugUI->SetUpdate(&RenderSystem::_DebugUI, this, MultiCore::BlockOpcode::eLast);

			IntrusivePtr<MultiCore::iSingleUpdateStage> endFrame;
			rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, endFrame.AsVoidPP());
			endFrame->Initialize(this, kEndFrame.GetString());
			endFrame->SetUpdate(&RenderSystem::_EndFrame, this, MultiCore::BlockOpcode::eLast);

			// Add the stages.
			AddStage(beginFrame);
			AddStage(drawInstances);
			AddStage(debugUI);
			AddStage(endFrame);

			// Add the default set of dependencies.
			AddDependency({
				{ GetID(), drawInstances->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), beginFrame->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), debugUI->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), drawInstances->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), endFrame->GetID(), MultiCore::iStage::kExecute },
				{ GetID(), debugUI->GetID(), MultiCore::iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			});

			return GOM::kOK;
		}
		return result;
	}
	return GOM::kInvalidParameter;
}

SystemID CPF_STDCALL RenderSystem::GetID() const
{
	return mID;
}

GOM::Result CPF_STDCALL RenderSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

GOM::Result CPF_STDCALL RenderSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

GOM::Result CPF_STDCALL RenderSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

GOM::Result CPF_STDCALL RenderSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

GOM::Result CPF_STDCALL RenderSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL RenderSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

GOM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}
