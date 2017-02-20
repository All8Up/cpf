//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Stage.hpp"
#include "Hash/Crc.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace MultiCore;

Stage::Stage(System* service, const String& name)
	: mpSystem(service)
	, mName(name)
	, mID(Platform::Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1)))
{
	
}

Stage::~Stage()
{}

System* Stage::GetSystem() const
{
	return mpSystem;
}

StageID Stage::GetID() const
{
	return mID;
}

const String& Stage::GetName() const
{
	return mName;
}

const Stage::Dependencies& Stage::GetDependencies() const
{
	return mDependencies;
}

//////////////////////////////////////////////////////////////////////////
namespace
{
	using StageMap = UnorderedMap<StageID, Stage::Creator>;
	StageMap s_StageMap;
}

bool Stage::Install(StageID id, Creator creator)
{
	if (s_StageMap.find(id) == s_StageMap.end())
	{
		s_StageMap[id] = creator;
		return true;
	}
	return false;
}

bool Stage::Remove(StageID id)
{
	if (s_StageMap.find(id) != s_StageMap.end())
	{
		s_StageMap.erase(id);
		return true;
	}
	return false;
}

Stage* Stage::_Create(StageID type, System* owner, const String& name)
{
	if (s_StageMap.find(type) != s_StageMap.end())
	{
		return (*s_StageMap[type])(owner, name);
	}
	return nullptr;
}


//////////////////////////////////////////////////////////////////////////

bool SingleUpdateStage::Install()
{
	return Stage::Install(kID, &SingleUpdateStage::_Creator);
}

bool SingleUpdateStage::Remove()
{
	return Stage::Remove(kID);
}

void SingleUpdateStage::Emit(Concurrency::Scheduler::Queue& q)
{
	q.FirstOne(&SingleUpdateStage::_Update, this);
}

void SingleUpdateStage::SetUpdate(Function<void(void*)> func, void* context)
{
	mpUpdate = func;
	mpContext = context;
}

SingleUpdateStage::SingleUpdateStage(System* owner, const String& name)
	: Stage(owner, name)
	, mpContext(nullptr)
{}

Stage* SingleUpdateStage::_Creator(System* owner, const String& name)
{
	return new SingleUpdateStage(owner, name);
}
void SingleUpdateStage::_Update(Concurrency::ThreadContext&, void* context)
{
	SingleUpdateStage* self = reinterpret_cast<SingleUpdateStage*>(context);
	if (self->mpUpdate)
		self->mpUpdate(self->mpContext);
}
