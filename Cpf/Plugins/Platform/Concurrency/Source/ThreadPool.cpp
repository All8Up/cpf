//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/iWorkBuffer.hpp"

using namespace Cpf;
using namespace Concurrency;

ThreadPool::ThreadPool(iBase*)
{
}

ThreadPool::~ThreadPool()
{
	mpScheduler->Shutdown();
}

GOM::Result CPF_STDCALL ThreadPool::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
			break;
		case iThreadPool::kIID.GetID():
			*outIface = static_cast<iThreadPool*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

bool ThreadPool::Initialize(Plugin::iRegistry* regy, int threadCount)
{
	if (GOM::Succeeded(regy->Create(nullptr, kSchedulerCID.GetID(), iScheduler::kIID.GetID(), mpScheduler.AsVoidPP())) &&
		GOM::Succeeded(regy->Create(nullptr, kWorkBufferCID.GetID(), iWorkBuffer::kIID.GetID(), mpQueue.AsVoidPP())))
		return GOM::Succeeded(mpScheduler->Initialize(threadCount, nullptr, nullptr, nullptr));
	return false;
}

void ThreadPool::Shutdown()
{
	mpScheduler->Shutdown();
}

void ThreadPool::Enqueue(WorkFunction task, void* context)
{
	mpQueue->FirstOne(task, context);
	mpScheduler->Execute(mpQueue, false);
}

int ThreadPool::GetAvailableThreads()
{
	return mpScheduler->GetMaxThreads();
}

void ThreadPool::SetActiveThreads(int count)
{
	mpScheduler->SetActiveThreads(count);
}

int ThreadPool::GetActiveThreads()
{
	return mpScheduler->GetActiveThreads();
}
