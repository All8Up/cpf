//////////////////////////////////////////////////////////////////////////
#include "GO/ObjectStage.hpp"
#include "MultiCore/Partitioning.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
ObjectStage::ObjectStage(MultiCore::System* owner, const String& name)
	: Stage(owner, name)
{
}

bool ObjectStage::Install()
{
	return Stage::Install(kID, &ObjectStage::_Creator);
}

bool ObjectStage::Remove()
{
	return Stage::Remove(kID);
}

MultiCore::Stage* ObjectStage::_Creator(MultiCore::System* owner, const String& name)
{
	return new ObjectStage(owner, name);
}

void ObjectStage::Emit(Concurrency::Scheduler::Queue& q)
{
	q.All(&ObjectStage::_Update, this);
}

void ObjectStage::AddUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f)
{
	mWork.Acquire();
	mWork.Add({ s, o, f });
	mWork.Release();
}

void ObjectStage::RemoveUpdate(MultiCore::System* s, iEntity* o, UpdateFunc f)
{
	mWork.Acquire();
	mWork.Remove({ s, o, f });
	mWork.Release();
}

void ObjectStage::_Update(Concurrency::ThreadContext& tc, void* context)
{
	ObjectStage& self = *reinterpret_cast<ObjectStage*>(context);
	MultiCore::EqualPartitions<MultiCore::SortedVectorContainer<UpdateTuple_t, Compare>, Caller>::Execute(self.mWork, tc, &self.mCaller);
}

bool ObjectStage::Compare::operator ()(const UpdateTuple_t& lhs, const UpdateTuple_t& rhs) const
{
	return CPF_STL_NAMESPACE::get<1>(lhs) < CPF_STL_NAMESPACE::get<1>(rhs);
}

void ObjectStage::Caller::Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work)
{
	(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
}
