//////////////////////////////////////////////////////////////////////////
#include "GO/Stage.hpp"
#include "MultiCore/Partitioning.hpp"

using namespace Cpf;
using namespace GO;

Stage::Stage(MultiCore::Service* service, System* system, MultiCore::StageID id, const Dependencies& dependencies)
	: MultiCore::Stage(service, id, dependencies)
	, mpSystem(system)
{}

void Stage::AddUpdate(System* s, Object* o, FuncType_t f)
{
	mWork.Acquire();
	mWork.Add({ s, o, f });
	mWork.Release();
}

void Stage::RemoveUpdate(System* s, Object* o, FuncType_t f)
{
	mWork.Acquire();
	mWork.Remove({ s, o, f });
	mWork.Release();
}

void Stage::Submit(Concurrency::Scheduler::Queue& q)
{
	q.All(&Stage::_Update, this);
}

System* Stage::GetSystem() const
{
	return mpSystem;
}

bool Stage::ResolveDependencies(GO::Service*, GO::System*)
{
	return true;
}

void Stage::_Update(Concurrency::ThreadContext& tc, void* context)
{
	Stage& self = *reinterpret_cast<Stage*>(context);
	MultiCore::EqualPartitions<MultiCore::SortedVectorContainer<UpdateTuple_t, Compare>, Caller>::Execute(self.mWork, tc, &self.mCaller);
}

void Stage::Caller::Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work)
{
	(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
}
