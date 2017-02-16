//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadContext.hpp"


using namespace Cpf::Concurrency;



ThreadContext::ThreadContext(Scheduler& scheduler, int threadId, void* userData)
	: mScheduler(scheduler)
	, mThreadId(threadId)
	, mpUserData(userData)
{

}


Scheduler& ThreadContext::GetScheduler() const
{
	return mScheduler;
}


int ThreadContext::GetThreadIndex() const
{
	return mThreadId;
}

int ThreadContext::GetThreadCount() const
{
	return mScheduler.mActiveCount;
}

void ThreadContext::SetUserData(void* data)
{
	CPF_ASSERT(mpUserData == nullptr);
	mpUserData = data;
}


int32_t& ThreadContext::TLD(int index) const
{
	return mScheduler._TLD(mThreadId, index);
}


void*& ThreadContext::TLA(int index) const
{
	return mScheduler._TLA(mThreadId, index);
}


int32_t& ThreadContext::SD(int index) const
{
	return mScheduler._SD(index);
}


void*& ThreadContext::SA(int index) const
{
	return mScheduler._SA(index);
}
