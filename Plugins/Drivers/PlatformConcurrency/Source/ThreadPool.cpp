//////////////////////////////////////////////////////////////////////////
#include "ThreadPool.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Platform;

ThreadPool::ThreadPool(Plugin::iRegistry* regy)
    : mpRegistry(regy)
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

GOM::Result ThreadPool::Initialize(int threadCount)
{
	if (GOM::Succeeded(mpRegistry->Create(nullptr, iScheduler::kCID, iScheduler::kIID, mpScheduler.AsVoidPP())) &&
		GOM::Succeeded(mpRegistry->Create(nullptr, iWorkBuffer::kCID, iWorkBuffer::kIID, mpQueue.AsVoidPP())))
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
