//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Scheduler.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		class ThreadContext
		{
		public:
			ThreadContext(Cpf::Concurrency::Scheduler&, int, void* userData=nullptr);

			Cpf::Concurrency::Scheduler& Scheduler() const;
			int ThreadId() const;
			int ThreadCount() const;
			void UserData(void*);
			template<typename TYPE=void>
			TYPE* UserData() const;

			// Register access.
			int32_t& TLD(int index) const;
			void*& TLA(int index) const;
			int32_t& SD(int index) const;
			void*& SA(int index) const;

		private:
			Cpf::Concurrency::Scheduler& mScheduler;
			int mThreadId;
			void* mpUserData;
		};


		template<typename TYPE>
		inline TYPE* Scheduler::ThreadContext::UserData() const
		{
			return reinterpret_cast<TYPE*>(mpUserData);
		}
	}
}
