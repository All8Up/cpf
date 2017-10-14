//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iStage.hpp"
#include "VTune/VTune.hpp"

using namespace CPF;
using namespace Concurrency;
using namespace MultiCore;

VTUNE_DOMAIN(RenderSystemDomain, "RenderSystem");

GOM::Result RenderSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kRenderSystemCID.GetID(), new Plugin::tClassInstance<RenderSystem>());
}

GOM::Result RenderSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kRenderSystemCID.GetID());
}

RenderSystem::RenderSystem(Plugin::iRegistry*, iUnknown*)
	: mpApp(nullptr)
	, mCurrentBackBuffer(0)
{
}

RenderSystem::~RenderSystem()
{}

void RenderSystem::_BeginFrame(const WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_BeginFrame(tc);
}
void RenderSystem::_Draw(const WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_Draw(tc);
}
void RenderSystem::_DebugUI(const WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_DebugUI(tc);
}
void RenderSystem::_EndFrame(const WorkContext* tc, void* context)
{
	RenderSystem* self = reinterpret_cast<RenderSystem*>(context);
	self->mpApp->_EndFrame(tc);
}


//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL RenderSystem::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
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
		auto result = rgy->Create(this, kStageListCID.GetID(), iStageList::kIID.GetID(), mpStages.AsVoidPP());
		if (GOM::Succeeded(result))
		{
			IntrusivePtr<iSingleUpdateStage> beginFrame;
			IntrusivePtr<iSingleUpdateStage> drawInstances;
			IntrusivePtr<iSingleUpdateStage> debugUI;
			IntrusivePtr<iSingleUpdateStage> endFrame;


#if 0
			struct InstructionBlockDesc
			{
				StageID mStageCID;
				const char* mpName;
				WorkFunction mpFunc;
				BlockOpcode mOpcode;
			};

			InstructionBlockDesc stageDescs[] =
			{
				{
					kSingleUpdateStageCID, "Begin Frame",
					&RenderSystem::_BeginFrame, BlockOpcode::eFirst
				},
				{
					drawInstances.AsVoidPP(),
					kSingleUpdateStageCID.GetID(), kDrawInstances.GetString(),
					&RenderSystem::_Draw, BlockOpcode::eLast
				},
				{
					debugUI.AsVoidPP(),
					kSingleUpdateStageCID.GetID(), kDebugUI.GetString(),
					&RenderSystem::_DebugUI, BlockOpcode::eLast
				},
				{
					endFrame.AsVoidPP(),
					kSingleUpdateStageCID.GetID(), kEndFrame.GetString(),
					&RenderSystem::_EndFrame, BlockOpcode::eLast
				}
			};
#endif

			/*
			if (GOM::Succeeded(AddStages(4, stageDescs)))
			{
				BlockDependency dependencies[] =
				{
					{
						{ GetID(), drawInstances->GetID(), iStage::kExecute },
						{ GetID(), beginFrame->GetID(), iStage::kExecute },
						DependencyPolicy::eAfter
					},
					{
						{ GetID(), debugUI->GetID(), iStage::kExecute },
						{ GetID(), drawInstances->GetID(), iStage::kExecute },
						DependencyPolicy::eAfter
					},
					{
						{ GetID(), endFrame->GetID(), iStage::kExecute },
						{ GetID(), debugUI->GetID(), iStage::kExecute },
						DependencyPolicy::eAfter
					}
				};

//				if (GOM::Succeeded(SetDependencies(3, dependencies)))
				{
//					return GOM::kOK;
				}
			}
			*/

			// Build the stages and set the update function for each.
			// NOTE: There are 4 stages which each depends on the prior to be complete
			// prior to execution..  Rather than insert barriers, this simply uses the
			// thread vm instruction 'last' which guarantee's that everything has completed
			// prior to entry.
			rgy->Create(nullptr, kSingleUpdateStageCID.GetID(), iSingleUpdateStage::kIID.GetID(), beginFrame.AsVoidPP());
			beginFrame->Initialize(this, kBeginFrame.GetString());
			beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, BlockOpcode::eFirst);

			// Paired in a group ^
			rgy->Create(nullptr, kSingleUpdateStageCID.GetID(), iSingleUpdateStage::kIID.GetID(), drawInstances.AsVoidPP());
			drawInstances->Initialize(this, kDrawInstances.GetString());
			drawInstances->SetUpdate(&RenderSystem::_Draw, this, BlockOpcode::eLast);

			rgy->Create(nullptr, kSingleUpdateStageCID.GetID(), iSingleUpdateStage::kIID.GetID(), debugUI.AsVoidPP());
			debugUI->Initialize(this, kDebugUI.GetString());
			debugUI->SetUpdate(&RenderSystem::_DebugUI, this, BlockOpcode::eLast);

			rgy->Create(nullptr, kSingleUpdateStageCID.GetID(), iSingleUpdateStage::kIID.GetID(), endFrame.AsVoidPP());
			endFrame->Initialize(this, kEndFrame.GetString());
			endFrame->SetUpdate(&RenderSystem::_EndFrame, this, BlockOpcode::eLast);

			// Add the stages.
			AddStage(beginFrame);
			AddStage(drawInstances);
			AddStage(debugUI);
			AddStage(endFrame);

			// Add the default set of dependencies.
			AddDependency({
				{ GetID(), drawInstances->GetID(), iStage::kExecute },
				{ GetID(), beginFrame->GetID(), iStage::kExecute },
				DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), debugUI->GetID(), iStage::kExecute },
				{ GetID(), drawInstances->GetID(), iStage::kExecute },
				DependencyPolicy::eAfter
			});
			AddDependency({
				{ GetID(), endFrame->GetID(), iStage::kExecute },
				{ GetID(), debugUI->GetID(), iStage::kExecute },
				DependencyPolicy::eAfter
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

GOM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iExecutionPlan* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}
