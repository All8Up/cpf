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

RenderSystem::RenderSystem(const String& name, const Desc* desc)
	: System(name)
	, mpApp(desc->mpApplication)
{
	{
		IntrusivePtr<MultiCore::SingleUpdateStage>
			ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Begin Frame")));
		ptr->SetUpdate(&RenderSystem::_BeginFrame, this);
		AddStage(ptr);
	}
	{
		IntrusivePtr<MultiCore::SingleUpdateStage>
			ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Clear Buffers")));
		ptr->SetUpdate(&RenderSystem::_Clear, this);
		ptr->SetDependencies({ { GetID(), MultiCore::StageID("Begin Frame"_crc64) } });
		AddStage(ptr);
	}
	{
		IntrusivePtr<MultiCore::SingleUpdateStage>
			ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Draw Instances")));
		ptr->SetUpdate(&RenderSystem::_Draw, this);
		ptr->SetDependencies({ { GetID(), MultiCore::StageID("Begin Frame"_crc64) } });
		AddStage(ptr);
	}
	{
		IntrusivePtr<MultiCore::SingleUpdateStage>
			ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Debug UI")));
		ptr->SetUpdate(&RenderSystem::_DebugUI, this, true, false);
		ptr->SetDependencies({
			{ GetID(), MultiCore::StageID("Begin Frame"_crc64) },
			{ GetID(), MultiCore::StageID("Clear Buffers"_crc64) },
			{ GetID(), MultiCore::StageID("Draw Instances"_crc64) }
		});
		AddStage(ptr);
	}
	{
		IntrusivePtr<MultiCore::SingleUpdateStage>
			ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Prepare Present")));
		ptr->SetUpdate(&RenderSystem::_PreparePresent, this);
		ptr->SetDependencies({
			{ GetID(), MultiCore::StageID("Debug UI"_crc64) }
		});
		AddStage(ptr);
	}
	{
		IntrusivePtr<MultiCore::SingleUpdateStage>
			ptr(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("End Frame")));
		ptr->SetUpdate(&RenderSystem::_EndFrame, this, true, false);
		ptr->SetDependencies({
			{ GetID(), MultiCore::StageID("Clear Buffers"_crc64) },
			{ GetID(), MultiCore::StageID("Prepare Present"_crc64) }
		});
		AddStage(ptr);
	}
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

MultiCore::System* RenderSystem::Creator(const String& name, const System::Desc* desc, const Dependencies& deps)
{
	return new RenderSystem(name, static_cast<const Desc*>(desc));
}
