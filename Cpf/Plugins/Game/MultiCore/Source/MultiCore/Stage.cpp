//////////////////////////////////////////////////////////////////////////
#include "MultiCore/iStage.hpp"
#include "Stage.hpp"
#include "PipelineBuilder.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
void SingleUpdateStage::SetUpdate(Function<void(const Concurrency::WorkContext*, void*)> func, void* context, BlockOpcode opcode)
{
	mOpcode = opcode;
	mpUpdate = func;
	mpContext = context;
}

GOM::Result CPF_STDCALL SingleUpdateStage::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;
		case iStage::kIID.GetID():
			*outIface = static_cast<iStage*>(this);
			break;
		case iSingleUpdateStage::kIID.GetID():
			*outIface = static_cast<iSingleUpdateStage*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL SingleUpdateStage::Initialize(iSystem* system, const char* const name)
{
	if (system && name)
	{
		mpSystem = system;
		mID = StageID(name, strlen(name));
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
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
GOM::Result CPF_STDCALL SingleUpdateStage::GetInstructions(int32_t* c, Instruction* i)
{
	if (c)
	{
		if (i)
		{
			*c = 1;
			i[0] = { { mpSystem->GetID(), GetID(), kExecute }, mOpcode, &SingleUpdateStage::_Update, this };
			return GOM::kOK;
		}
		*c = 1;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL SingleUpdateStage::GetDependencies(int32_t* count, BlockDependency* dependencies)
{
	(void)dependencies;
	if (count)
	{
		*count = 0;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

SingleUpdateStage::SingleUpdateStage(iBase*)
	: mpUpdate(nullptr)
	, mpContext(nullptr)
	, mOpcode(BlockOpcode::eFirst)
	, mEnabled(true)
{
}

void SingleUpdateStage::_Update(const Concurrency::WorkContext* tc, void* context)
{
	SingleUpdateStage* self = reinterpret_cast<SingleUpdateStage*>(context);
	if (self->mpUpdate)
		self->mpUpdate(tc, self->mpContext);
}
