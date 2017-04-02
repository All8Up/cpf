//////////////////////////////////////////////////////////////////////////
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "MultiCore/Partitioning.hpp"
#include "MultiCore/QueueBuilder.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
EntityStage::EntityStage(MultiCore::iSystem* owner, const char* name)
{
	Initialize(owner, name);
}

bool EntityStage::Install()
{
	return Stage::Install(kID, &EntityStage::_Creator);
}

bool EntityStage::Remove()
{
	return Stage::Remove(kID);
}

MultiCore::Stage* EntityStage::_Creator(Plugin::iRegistry* rgy, MultiCore::iSystem* owner, const char* name)
{
	return new EntityStage(owner, name);
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

COM::Result CPF_STDCALL EntityStage::GetDependencies(MultiCore::SystemID sid, int32_t* count, MultiCore::BlockDependency* deps)
{
	if (count)
	{
		*count = 2;
		if (deps)
		{
			deps[0] = {
				{ sid, GetID(), Stage::kEnd },
				{ sid, GetID(), Stage::kExecute },
				MultiCore::DependencyPolicy::eAfter
			};
			deps[1] = {
				{ sid, GetID(), Stage::kExecute },
				{ sid, GetID(), Stage::kBegin },
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
