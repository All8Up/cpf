//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadContext.hpp"


using namespace Cpf::Concurrency;



ThreadContext::ThreadContext(Cpf::Concurrency::Scheduler& scheduler, int threadId, void* userData)
	: mScheduler(scheduler)
	, mThreadId(threadId)
	, mpUserData(userData)
{

}


Cpf::Concurrency::Scheduler& ThreadContext::Scheduler() const
{
	return mScheduler;
}


int ThreadContext::ThreadId() const
{
	return mThreadId;
}

int ThreadContext::ThreadCount() const
{
	return mScheduler.mActiveCount;
}

void ThreadContext::UserData(void* data)
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
