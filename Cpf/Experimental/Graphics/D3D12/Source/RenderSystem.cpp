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

RenderSystem::RenderSystem(MultiCore::iPipeline* owner, const char* name, const Desc* desc)
	: System(owner, name)
	, mpApp(desc->mpApplication)
	, mCurrentBackBuffer(0)
{
	// Build the stages and set the update function for each.
	// NOTE: While there are 6 stages which must operate in order, there will only
	// be two required barrier groups since the only thing required is that they
	// run in order which is accomplished via series of eLast types.
	IntrusivePtr<MultiCore::SingleUpdateStage> beginFrame(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, this, kBeginFrame.GetString())));
	beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, MultiCore::BlockOpcode::eFirst);
	// Paired in a group ^
	IntrusivePtr<MultiCore::SingleUpdateStage> clearBuffers(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, this, kClearBuffers.GetString())));
	clearBuffers->SetUpdate(&RenderSystem::_Clear, this, MultiCore::BlockOpcode::eLast);

	IntrusivePtr<MultiCore::SingleUpdateStage> drawInstances(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, this, kDrawInstances.GetString())));
	drawInstances->SetUpdate(&RenderSystem::_Draw, this, MultiCore::BlockOpcode::eLast);
	IntrusivePtr<MultiCore::SingleUpdateStage> debugUI(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, this, kDebugUI.GetString())));
	debugUI->SetUpdate(&RenderSystem::_DebugUI, this, MultiCore::BlockOpcode::eLast);
	IntrusivePtr<MultiCore::SingleUpdateStage> preparePresent(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, this, kPreparePresent.GetString())));
	preparePresent->SetUpdate(&RenderSystem::_PreparePresent, this, MultiCore::BlockOpcode::eLast);
	IntrusivePtr<MultiCore::SingleUpdateStage> endFrame(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, this, kEndFrame.GetString())));
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
		{ GetID(), clearBuffers->GetID(), MultiCore::Stage::kExecute },
		{ GetID(), beginFrame->GetID(), MultiCore::Stage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});
	AddDependency({
		{ GetID(), drawInstances->GetID(), MultiCore::Stage::kExecute },
		{ GetID(), clearBuffers->GetID(), MultiCore::Stage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});
	AddDependency({
		{ GetID(), debugUI->GetID(), MultiCore::Stage::kExecute },
		{ GetID(), drawInstances->GetID(), MultiCore::Stage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});
	AddDependency({
		{ GetID(), preparePresent->GetID(), MultiCore::Stage::kExecute },
		{ GetID(), debugUI->GetID(), MultiCore::Stage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});
	AddDependency({
		{ GetID(), endFrame->GetID(), MultiCore::Stage::kExecute },
		{ GetID(), preparePresent->GetID(), MultiCore::Stage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});

	_AllocateBuffers();
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

MultiCore::System* RenderSystem::Creator(MultiCore::iPipeline* owner, const char* name, const System::Desc* desc)
{
	return new RenderSystem(owner, name, static_cast<const Desc*>(desc));
}
