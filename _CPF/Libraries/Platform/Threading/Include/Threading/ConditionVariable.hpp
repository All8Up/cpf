//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Platform/Threading/Types.hpp"
#include "Time/Value.hpp"
#include "Functional.hpp"

namespace CPF
{
	namespace Threading
	{
		// Forward references.
		class Mutex;

		//////////////////////////////////////////////////////////////////////////
		/// Thread synchronization condition variable.
		//////////////////////////////////////////////////////////////////////////
		class ConditionVariable
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Predicate_t = Function<bool()>;

			//////////////////////////////////////////////////////////////////////////
			ConditionVariable();
			~ConditionVariable();

			//////////////////////////////////////////////////////////////////////////
			void Acquire(Mutex&);
			void Acquire(Mutex&, Predicate_t&&);
			bool TimedAcquire(Mutex&, const Time::Value);

			void Release();
			void ReleaseAll();

		private:
			//////////////////////////////////////////////////////////////////////////
			ConditionVariable(ConditionVariable&&) = delete;
			ConditionVariable(const ConditionVariable&) = delete;
			ConditionVariable& operator =(ConditionVariable&&) = delete;
			ConditionVariable& operator =(const ConditionVariable&) = delete;

			//////////////////////////////////////////////////////////////////////////
			ConditionVariable_t m_ConditionVar;	//! Os specific condition variable storage.
		};
	}
}
#include "Platform/Threading/ConditionVariable.hpp"
