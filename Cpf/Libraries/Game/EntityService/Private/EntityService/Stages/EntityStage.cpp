//////////////////////////////////////////////////////////////////////////
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "MultiCore/Partitioning.hpp"
#include "MultiCore/QueueBuilder.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
EntityStage::EntityStage()
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

COM::Result CPF_STDCALL EntityStage::QueryInterface(COM::InterfaceID id, void** outIface)
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
		case iEntityStage::kIID.GetID():
			*outIface = static_cast<iEntityStage*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL EntityStage::Initialize(MultiCore::iSystem* owner, const char* const name)
{
	if (owner && name)
	{
		mpSystem = owner;
		mID = MultiCore::StageID(name, strlen(name));
		return COM::kOK;
	}
	return COM::kInvalidParameter;
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

COM::Result CPF_STDCALL EntityStage::GetDependencies(MultiCore::SystemID sid, int32_t* count, MultiCore::BlockDependency* deps)
{
	if (count)
	{
		*count = 2;
		if (deps)
		{
			deps[0] = {
				{ sid, GetID(), iStage::kEnd },
				{ sid, GetID(), iStage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			};
			deps[1] = {
				{ sid, GetID(), iStage::kExecute },
				{ sid, GetID(), iStage::kBegin },
				MultiCore::DependencyPolicy::eBarrier
			};
		}
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result EntityStage::GetInstructions(MultiCore::SystemID sid, int32_t* count, MultiCore::Instruction* instructions)
{
	if (count)
	{
		if (instructions)
		{
			*count = 3;
			instructions[0] = { { sid, GetID(), kBegin }, MultiCore::BlockOpcode::eFirst, &EntityStage::_Begin, this };
			instructions[1] = { { sid, GetID(), kExecute }, MultiCore::BlockOpcode::eAll, &EntityStage::_Update, this };
			instructions[2] = { { sid, GetID(), kEnd }, MultiCore::BlockOpcode::eLast, &EntityStage::_End, this };
			return COM::kOK;
		}
		*count = 3;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void EntityStage::_Begin(Concurrency::ThreadContext& tc, void* context)
{
	(void)tc;
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	self.mWork.Begin();
}

void EntityStage::_Update(Concurrency::ThreadContext& tc, void* context)
{
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	MultiCore::EqualPartitions<MultiCore::SortedVectorContainer<UpdateTuple_t, Compare>, Caller>::Execute(self.mWork, tc, &self.mCaller);
}

void EntityStage::_End(Concurrency::ThreadContext& tc, void* context)
{
	(void)tc;
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	self.mWork.End();
}

bool EntityStage::Compare::operator ()(const UpdateTuple_t& lhs, const UpdateTuple_t& rhs) const
{
	return CPF_STL_NAMESPACE::get<1>(lhs) < CPF_STL_NAMESPACE::get<1>(rhs);
}

void EntityStage::Caller::Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work)
{
	(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
}
