//////////////////////////////////////////////////////////////////////////
#include "Threading/ConditionVariable.hpp"
#include "Threading/Mutex.hpp"
#include <time.h>


namespace Cpf
{
	namespace Threading
	{
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
				pthread_cond_wait(&m_ConditionVar, &mtx.NativeHandle());
				if (predicate())
					return;
				mtx.Release();
			}
		}


		bool ConditionVariable::TimedAcquire(Mutex& mtx, const Cpf::Time::Value duration)
		{
			Cpf::Time::Value time = Cpf::Time::Value::Now() + duration;

			struct timespec abstime;

			uint64_t nstime = Cpf::Time::Unit::Ns(time);
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
	}
}
