//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/Stage.hpp"

using namespace Cpf;
using namespace Concurrency;

bool RenderSystem::Install()
{
	return System::Install(kID, &RenderSystem::Creator);
}

bool RenderSystem::Remove()
{
	return System::Remove(kID);
}

RenderSystem::RenderSystem(const String& name, const EntityService::SystemDependencies& deps, const Desc* desc)
	: System(name, deps)
	, mpApp(desc->mpApplication)
{
	// Build the stages and set the update function for each.
	IntrusivePtr<MultiCore::SingleUpdateStage> beginFrame(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kBeginFrame.GetString()));
	beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this);

	IntrusivePtr<MultiCore::SingleUpdateStage> clearBuffers(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kClearBuffers.GetString()));
	clearBuffers->SetUpdate(&RenderSystem::_Clear, this);

	IntrusivePtr<MultiCore::SingleUpdateStage> drawInstances(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kDrawInstances.GetString()));
	drawInstances->SetUpdate(&RenderSystem::_Draw, this);

	IntrusivePtr<MultiCore::SingleUpdateStage> debugUI(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kDebugUI.GetString()));
	debugUI->SetUpdate(&RenderSystem::_DebugUI, this, true, false);

	IntrusivePtr<MultiCore::SingleUpdateStage> preparePresent(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kPreparePresent.GetString()));
	preparePresent->SetUpdate(&RenderSystem::_PreparePresent, this);

	IntrusivePtr<MultiCore::SingleUpdateStage> endFrame(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kEndFrame.GetString()));
	endFrame->SetUpdate(&RenderSystem::_EndFrame, this, true, false);

	// Add the stages.
	AddStage(beginFrame);
	AddStage(clearBuffers);
	AddStage(drawInstances);
	AddStage(debugUI);
	AddStage(preparePresent);
	AddStage(endFrame);

	// Add the default set of dependencies.
	AddDependency({ clearBuffers->GetID(),{ GetID(), beginFrame->GetID() } });
	AddDependency({ drawInstances->GetID(),{ GetID(), clearBuffers->GetID() } });
	AddDependency({ debugUI->GetID(),{ GetID(), drawInstances->GetID() } });
	AddDependency({ preparePresent->GetID(),{ GetID(), debugUI->GetID() } });
	AddDependency({ endFrame->GetID(),{ GetID(), preparePresent->GetID() } });
}

RenderSystem::~RenderSystem()
{}

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

MultiCore::System* RenderSystem::Creator(const String& name, const System::Desc* desc, const EntityService::SystemDependencies& deps)
{
	return new RenderSystem(name, deps, static_cast<const Desc*>(desc));
}
