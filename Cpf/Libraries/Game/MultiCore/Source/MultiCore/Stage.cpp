//////////////////////////////////////////////////////////////////////////
#include "MultiCore/iStage.hpp"
#include "Stage.hpp"
#include "MultiCore/QueueBuilder.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
namespace
{
	using StageMap = UnorderedMap<StageID, Stage::Creator>;
	StageMap s_StageMap;
}

bool iStage::Install(StageID id, Creator creator)
{
	if (s_StageMap.find(id) == s_StageMap.end())
	{
		s_StageMap[id] = creator;
		return true;
	}
	return false;
}

bool iStage::Remove(StageID id)
{
	if (s_StageMap.find(id) != s_StageMap.end())
	{
		s_StageMap.erase(id);
		return true;
	}
	return false;
}

iStage* iStage::Create(StageID type, Plugin::iRegistry* rgy, iSystem* owner, const char* name)
{
	if (s_StageMap.find(type) != s_StageMap.end())
	{
		return (*s_StageMap[type])(rgy, owner, name);
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
Stage::Stage()
	: mEnabled(true)
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

COM::Result CPF_STDCALL Stage::Initialize(iSystem* system, const char* const name)
{
	if (system && name)
	{
		mpSystem = system;
		mID = StageID(name, strlen(name));
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

iSystem* Stage::GetSystem() const
{
	return mpSystem;
}

StageID CPF_STDCALL Stage::GetID() const
{
	return mID;
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
	(void)instructions;
	if (count)
	{
		*count = 0;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Stage::GetDependencies(SystemID, int32_t* count, BlockDependency* dependencies)
{
	(void)dependencies;
	if (count)
	{
		*count = 0;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}


//////////////////////////////////////////////////////////////////////////
void SingleUpdateStage::SetUpdate(Function<void(Concurrency::ThreadContext&, void*)> func, void* context, BlockOpcode opcode)
{
	mOpcode = opcode;
	mpUpdate = func;
	mpContext = context;
}

COM::Result CPF_STDCALL SingleUpdateStage::QueryInterface(COM::InterfaceID id, void** outIface)
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
		case iSingleUpdateStage::kIID.GetID():
			*outIface = static_cast<iSingleUpdateStage*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL SingleUpdateStage::Initialize(iSystem* system, const char* const name)
{
	if (system && name)
	{
		mpSystem = system;
		mID = StageID(name, strlen(name));
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

iSystem* SingleUpdateStage::GetSystem() const
{
	return mpSystem;
}

StageID CPF_STDCALL SingleUpdateStage::GetID() const
{
	return mID;
}


bool SingleUpdateStage::IsEnabled() const
{
	return mEnabled;
}

void SingleUpdateStage::SetEnabled(bool flag)
{
	mEnabled = flag;
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

COM::Result CPF_STDCALL SingleUpdateStage::GetDependencies(SystemID, int32_t* count, BlockDependency* dependencies)
{
	(void)dependencies;
	if (count)
	{
		*count = 0;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

SingleUpdateStage::SingleUpdateStage()
	: mpUpdate(nullptr)
	, mpContext(nullptr)
	, mOpcode(BlockOpcode::eFirst)
{
}

void SingleUpdateStage::_Update(Concurrency::ThreadContext& tc, void* context)
{
	SingleUpdateStage* self = reinterpret_cast<SingleUpdateStage*>(context);
	if (self->mpUpdate)
		self->mpUpdate(tc, self->mpContext);
}
