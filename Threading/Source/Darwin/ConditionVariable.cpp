//////////////////////////////////////////////////////////////////////////
#include "Threading/ConditionVariable.hpp"
#include "Threading/Mutex.hpp"
#include <time.h>

using namespace Cpf;
using namespace Platform;
using namespace Threading;

ConditionVariable::ConditionVariable()
{
	pthread_cond_init(&m_ConditionVar, nullptr);
}


ConditionVariable::~ConditionVariable()
{
	pthread_cond_destroy(&m_ConditionVar);
}


void ConditionVariable::Acquire(Mutex& mtx)
{
	pthread_cond_wait(&m_ConditionVar, &mtx.NativeHandle());
}


void ConditionVariable::Acquire(Mutex& mtx, Predicate_t&& predicate)
{
	for(;;)
	{
		if (predicate())
			return;
		pthread_cond_wait(&m_ConditionVar, &mtx.NativeHandle());
	}
}


bool ConditionVariable::TimedAcquire(Mutex& mtx, const Time::Value duration)
{
	Time::Value time = Time::Value::Now() + duration;

	struct timespec abstime;

	uint64_t nstime = Time::Ns(time);
	abstime.tv_sec = nstime/1000000000;
	abstime.tv_nsec = nstime%1000000000;

	return pthread_cond_timedwait(&m_ConditionVar, &mtx.NativeHandle(), &abstime) == 0;
}


void ConditionVariable::Release()
{
	pthread_cond_signal(&m_ConditionVar);
}


void ConditionVariable::ReleaseAll()
{
	pthread_cond_broadcast(&m_ConditionVar);
}
