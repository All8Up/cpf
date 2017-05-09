//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/iWorkBuffer.hpp"

using namespace Cpf;
using namespace Concurrency;

ThreadPool::ThreadPool(iUnknown*)
{
}

ThreadPool::~ThreadPool()
{
	mpScheduler->Shutdown();
}

COM::Result CPF_STDCALL ThreadPool::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case iThreadPool::kIID.GetID():
			*outIface = static_cast<iThreadPool*>(this);
			break;

		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool ThreadPool::Initialize(Plugin::iRegistry* regy, int threadCount)
{
	if (Succeeded(regy->Create(nullptr, kSchedulerCID, iScheduler::kIID, mpScheduler.AsVoidPP())) &&
		Succeeded(regy->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, mpQueue.AsVoidPP())))
		return Succeeded(mpScheduler->Initialize(threadCount, nullptr, nullptr, nullptr));
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
