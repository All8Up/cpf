//
#pragma once
#include "Configuration.hpp"
#include <pthread.h>


namespace Cpf
{
	namespace Platform
	{
		namespace Threading
		{
			typedef pthread_t Thread_t;
			const Thread_t InvalidThread = {0};

			typedef pthread_cond_t ConditionVariable_t;
			const ConditionVariable_t InvalidConditionVariable = {0};

			typedef pthread_mutex_t Mutex_t;
			const Mutex_t InvalidMutex = {0};

			struct Semaphore_t
			{
				pthread_mutex_t	m_Mutex;
				pthread_cond_t	m_Condition;
				uint32_t		m_Count;
			};
			const Semaphore_t InvalidSemaphore = {InvalidMutex, InvalidConditionVariable, 0};

			typedef pthread_key_t ThreadLocal_t;
			const ThreadLocal_t InvalidThreadLocal = {0};
		}
	}
}
