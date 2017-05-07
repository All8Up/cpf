//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Mutex.hpp"

namespace Cpf
{
	namespace Threading
	{
		inline ConditionVariable::ConditionVariable()
		{
			::InitializeConditionVariable(&m_ConditionVar);
		}


		inline ConditionVariable::~ConditionVariable()
		{}


		/**
		@brief Attempt to acquire the condition variable.  Condition variables are subject to spurious wakeup.
		@param mtx The mutex used to control access.
		*/
		inline void ConditionVariable::Acquire(Mutex& mtx)
		{
			SleepConditionVariableCS(&m_ConditionVar, &mtx.NativeHandle(), INFINITE);
		}


		/**
		@brief Attempt to acquire the condition variable, checking the predicate to prevent spurious wakeup.
		@param mtx The mutex used to control access.
		@param predicate The predicate function to validate that the condition is valid.
		*/
		inline void ConditionVariable::Acquire(Mutex& mtx, Predicate_t&& predicate)
		{
			for (;;)
			{
				if (predicate())
					return;
				SleepConditionVariableCS(&m_ConditionVar, &mtx.NativeHandle(), INFINITE);
			}
		}


		/**
		@brief Attempt to acquire the condition variable until the timeout expires.
		@param mtx The mutex used to control access.
		@param timeout The timeout before the attempt gives up.
		*/
		inline bool ConditionVariable::TimedAcquire(Mutex& mtx, const Time::Value timeout)
		{
			return SleepConditionVariableCS(&m_ConditionVar, &mtx.NativeHandle(), DWORD(int64_t(Time::Ms(timeout)))) != 0;
		}


		/**
		@brief Allow a single thread to acquire the condition variable.
		*/
		inline void ConditionVariable::Release()
		{
			WakeConditionVariable(&m_ConditionVar);
		}


		/**
		@brief Allow any waiting threads to acquire the condition variable.
		*/
		inline void ConditionVariable::ReleaseAll()
		{
			WakeAllConditionVariable(&m_ConditionVar);
		}
	}
}
