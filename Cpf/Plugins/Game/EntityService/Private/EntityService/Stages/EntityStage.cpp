//////////////////////////////////////////////////////////////////////////
#include "EntityStage.hpp"
#include "MultiCore/Partitioning.hpp"

using namespace CPF;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
EntityStage::EntityStage(iUnknown*)
	: mpSystem(nullptr)
	, mEnabled(true)
{
}

void EntityStage::AddUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f)
{
	mWork.Acquire();
	mWork.Add({ s, o, f });
	mWork.Release();
}

void EntityStage::RemoveUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f)
{
	mWork.Acquire();
	mWork.Remove({ s, o, f });
	mWork.Release();
}

GOM::Result CPF_STDCALL EntityStage::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iStage::kIID.GetID():
			*outIface = static_cast<iStage*>(this);
			break;
		case iEntityStage::kIID.GetID():
			*outIface = static_cast<iEntityStage*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL EntityStage::Initialize(MultiCore::iSystem* owner, const char* const name)
{
	if (owner && name)
	{
		mpSystem = owner;
		mID = MultiCore::StageID(name, strlen(name));
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

MultiCore::iSystem* CPF_STDCALL EntityStage::GetSystem() const
{
	return mpSystem;
}

MultiCore::StageID CPF_STDCALL EntityStage::GetID() const
{
	return mID;
}

bool CPF_STDCALL EntityStage::IsEnabled() const
{
	return mEnabled;
}

void CPF_STDCALL EntityStage::SetEnabled(bool flag)
{
	mEnabled = flag;
}

GOM::Result CPF_STDCALL EntityStage::GetDependencies(int32_t* count, MultiCore::BlockDependency* deps)
{
	if (count)
	{
		*count = 2;
		if (deps)
		{
			deps[0] = {
				{ mpSystem->GetID(), GetID(), iStage::kEnd },
				{ mpSystem->GetID(), GetID(), iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			};
			deps[1] = {
				{ mpSystem->GetID(), GetID(), iStage::kExecute },
				{ mpSystem->GetID(), GetID(), iStage::kBegin },
				MultiCore::DependencyPolicy::eBarrier
			};
		}
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result EntityStage::GetInstructions(int32_t* count, MultiCore::Instruction* instructions)
{
	if (count)
	{
		if (instructions)
		{
			*count = 3;
			instructions[0] = { { mpSystem->GetID(), GetID(), kBegin }, MultiCore::BlockOpcode::eFirst, &EntityStage::_Begin, this };
			instructions[1] = { { mpSystem->GetID(), GetID(), kExecute }, MultiCore::BlockOpcode::eAll, &EntityStage::_Update, this };
			instructions[2] = { { mpSystem->GetID(), GetID(), kEnd }, MultiCore::BlockOpcode::eLast, &EntityStage::_End, this };
			return GOM::kOK;
		}
		*count = 3;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void EntityStage::_Begin(const Concurrency::WorkContext* tc, void* context)
{
	(void)tc;
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	self.mWork.Begin();
}

void EntityStage::_Update(const Concurrency::WorkContext* tc, void* context)
{
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	MultiCore::EqualPartitions<MultiCore::SortedVectorContainer<UpdateTuple_t, Compare>, Caller>::Execute(self.mWork, tc, &self.mCaller);
}

void EntityStage::_End(const Concurrency::WorkContext* tc, void* context)
{
	(void)tc;
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	self.mWork.End();
}

bool EntityStage::Compare::operator ()(const UpdateTuple_t& lhs, const UpdateTuple_t& rhs) const
{
	return CPF_STL_NAMESPACE::get<1>(lhs) < CPF_STL_NAMESPACE::get<1>(rhs);
}

void EntityStage::Caller::Execute(const Concurrency::WorkContext*, const UpdateTuple_t& work)
{
	(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
}
