//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadPool.hpp"

using namespace Cpf;
using namespace Concurrency;

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
	mScheduler.Shutdown();
}

bool ThreadPool::Initialize(Platform::Threading::Thread::Group&& group)
{
	return mScheduler.Initialize(Move(group));
}

void ThreadPool::Shutdown()
{
	mScheduler.Shutdown();
}

void ThreadPool::Enqueue(Task task, void* context)
{
	mQueue.FirstOne(task, context);
	mScheduler.Execute(mQueue, false);
}

int ThreadPool::GetAvailableThreads() const
{
	return mScheduler.GetAvailableThreads();
}

void ThreadPool::SetActiveThreads(int count)
{
	mScheduler.SetActiveThreads(count);
}
