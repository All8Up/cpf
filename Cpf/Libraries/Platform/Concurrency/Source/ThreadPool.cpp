//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadPool.hpp"

using namespace Cpf;
using namespace Concurrency;

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
	mpScheduler->Shutdown();
}

bool ThreadPool::Initialize(Plugin::iRegistry* regy, int threadCount)
{
	if (Succeeded(regy->Create(nullptr, kSchedulerCID, iScheduler::kIID, mpScheduler.AsVoidPP())))
		return Succeeded(mpScheduler->Initialize(threadCount, nullptr, nullptr, nullptr));
	return false;
}

void ThreadPool::Shutdown()
{
	mpScheduler->Shutdown();
}

void ThreadPool::Enqueue(Task task, void* context)
{
	mQueue.FirstOne(task, context);
	mpScheduler->Execute(static_cast<iQueue*>(&mQueue), false);
}

int ThreadPool::GetAvailableThreads() const
{
	return mpScheduler->GetMaxThreads();
}

void ThreadPool::SetActiveThreads(int count)
{
	mpScheduler->SetActiveThreads(count);
}

int ThreadPool::GetActiveThreads() const
{
	return mpScheduler->GetActiveThreads();
}
