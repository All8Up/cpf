//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadPool.hpp"

using namespace Cpf;
using namespace Concurrency;

ThreadPool::ThreadPool()
	: mScheduler(nullptr)
{
}

ThreadPool::~ThreadPool()
{
	mScheduler.Shutdown();
}

bool ThreadPool::Initialize(int threadCount)
{
	return COM::Succeeded(mScheduler.Initialize(threadCount, nullptr, nullptr, nullptr));
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

int ThreadPool::GetActiveThreads() const
{
	return mScheduler.GetCurrentThreads();
}
