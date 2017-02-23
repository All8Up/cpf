//////////////////////////////////////////////////////////////////////////
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "MultiCore/Partitioning.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
EntityStage::EntityStage(MultiCore::System* owner, const String& name)
	: Stage(owner, name)
{
}

bool EntityStage::Install()
{
	return Stage::Install(kID, &EntityStage::_Creator);
}

bool EntityStage::Remove()
{
	return Stage::Remove(kID);
}

MultiCore::Stage* EntityStage::_Creator(MultiCore::System* owner, const String& name)
{
	return new EntityStage(owner, name);
}

void EntityStage::Emit(Concurrency::Scheduler::Queue& q)
{
	q.All(&EntityStage::_Update, this);
}

void EntityStage::AddUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f)
{
	mWork.Acquire();
	mWork.Add({ s, o, f });
	mWork.Release();
}

void EntityStage::RemoveUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f)
{
	mWork.Acquire();
	mWork.Remove({ s, o, f });
	mWork.Release();
}

void EntityStage::_Update(Concurrency::ThreadContext& tc, void* context)
{
	EntityStage& self = *reinterpret_cast<EntityStage*>(context);
	MultiCore::EqualPartitions<MultiCore::SortedVectorContainer<UpdateTuple_t, Compare>, Caller>::Execute(self.mWork, tc, &self.mCaller);
}

bool EntityStage::Compare::operator ()(const UpdateTuple_t& lhs, const UpdateTuple_t& rhs) const
{
	return CPF_STL_NAMESPACE::get<1>(lhs) < CPF_STL_NAMESPACE::get<1>(rhs);
}

void EntityStage::Caller::Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work)
{
	(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
}
