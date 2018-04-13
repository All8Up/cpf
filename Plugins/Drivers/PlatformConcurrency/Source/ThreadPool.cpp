//////////////////////////////////////////////////////////////////////////
#include "ThreadPool.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Concurrency;

ThreadPool::ThreadPool(Plugin::iRegistry*, iUnknown*)
{
}

ThreadPool::~ThreadPool()
{
	mpScheduler->Shutdown();
}

GOM::Result CPF_STDCALL ThreadPool::QueryInterface(GOM::IID id, void** outIface)
{
	if (outIface)
	{
		switch (uint64_t(id))
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
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

GOM::Result ThreadPool::Initialize(Plugin::iRegistry* regy, int threadCount)
{
	if (GOM::Succeeded(regy->Create(nullptr, iScheduler::kCID, iScheduler::kIID, mpScheduler.AsVoidPP())) &&
		GOM::Succeeded(regy->Create(nullptr, iWorkBuffer::kCID, iWorkBuffer::kIID, mpQueue.AsVoidPP())))
		return mpScheduler->Initialize(threadCount, nullptr, nullptr, nullptr);
	return GOM::kError;
}

void ThreadPool::Shutdown()
{
	mpScheduler->Shutdown();
}

void ThreadPool::Enqueue(WorkFunction task, void* context)
{
	mpQueue->FirstOne(task, context);
	mpScheduler->Execute(mpQueue);
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
