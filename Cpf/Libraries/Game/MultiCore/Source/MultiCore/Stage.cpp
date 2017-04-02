//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Stage.hpp"
#include "MultiCore/QueueBuilder.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace MultiCore;

Stage::Stage(System* service, const char* name)
	: mpSystem(service)
	, mID(name, strlen(name))
	, mEnabled(true)
{
	
}

Stage::~Stage()
{}

COM::Result CPF_STDCALL Stage::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iStage::kIID.GetID():
			*outIface = static_cast<iStage*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

System* Stage::GetSystem() const
{
	return mpSystem;
}

StageID CPF_STDCALL Stage::GetID() const
{
	return mID;
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

Stage* Stage::_Create(StageID type, System* owner, const char* name)
{
	if (s_StageMap.find(type) != s_StageMap.end())
	{
		return (*s_StageMap[type])(owner, name);
	}
	return nullptr;
}

bool Stage::IsEnabled() const
{
	return mEnabled;
}

void Stage::SetEnabled(bool flag)
{
	mEnabled = flag;
}

COM::Result CPF_STDCALL Stage::GetInstructions(SystemID, int32_t* count, Instruction* instructions)
{
	if (count)
	{
		if (instructions)
		{
			*count = 0;
			return COM::kOK;
		}
		*count = 0;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Stage::GetDependencies(SystemID, int32_t* count, BlockDependency* dependencies)
{
	if (count)
	{
		if (dependencies)
		{
			*count = 0;
			return COM::kOK;
		}
		*count = 0;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
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

void SingleUpdateStage::SetUpdate(Function<void(Concurrency::ThreadContext&, void*)> func, void* context, BlockOpcode opcode)
{
	mOpcode = opcode;
	mpUpdate = func;
	mpContext = context;
}

COM::Result CPF_STDCALL SingleUpdateStage::GetInstructions(SystemID sid, int32_t* c, Instruction* i)
{
	if (c)
	{
		if (i)
		{
			*c = 1;
			i[0] = { { sid, GetID(), kExecute }, mOpcode, &SingleUpdateStage::_Update, this };
			return COM::kOK;
		}
		*c = 1;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}


SingleUpdateStage::SingleUpdateStage(System* owner, const char* name)
	: Stage(owner, name)
	, mpUpdate(nullptr)
	, mpContext(nullptr)
	, mOpcode(BlockOpcode::eFirst)
{}

Stage* SingleUpdateStage::_Creator(System* owner, const char* name)
{
	return new SingleUpdateStage(owner, name);
}
void SingleUpdateStage::_Update(Concurrency::ThreadContext& tc, void* context)
{
	SingleUpdateStage* self = reinterpret_cast<SingleUpdateStage*>(context);
	if (self->mpUpdate)
		self->mpUpdate(tc, self->mpContext);
}
