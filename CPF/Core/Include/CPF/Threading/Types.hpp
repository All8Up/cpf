//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	namespace Threading
	{
		/**
		 * Os Specific thread handle.
		 */
		typedef HANDLE Thread_t;
		const Thread_t InvalidThread = nullptr;

		typedef CRITICAL_SECTION Mutex_t;
		const CRITICAL_SECTION InvalidMutex = { 0 };

		typedef HANDLE Semaphore_t;
		const Semaphore_t InvalidSemaphore = nullptr;

		typedef CONDITION_VARIABLE ConditionVariable_t;
		const CONDITION_VARIABLE InvalidConditionVariable = { 0 };

		typedef DWORD ThreadLocal_t;
		const ThreadLocal_t InvalidThreadLocal = TLS_OUT_OF_INDEXES;
	}
}
