//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Scheduler.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		class CPF_EXPORT_CONCURRENCY ThreadContext
		{
		public:
			ThreadContext(Scheduler&, int, void* userData=nullptr);

			Scheduler& GetScheduler() const;
			int GetThreadIndex() const;
			int GetThreadCount() const;
			void SetUserData(void*);
			template<typename TYPE=void>
			TYPE* GetUserData() const;

			// Register access.
			int32_t& TLD(int index) const;
			void*& TLA(int index) const;
			int32_t& SD(int index) const;
			void*& SA(int index) const;

		private:
			Concurrency::Scheduler& mScheduler;
			int mThreadId;
			void* mpUserData;
		};


		template<typename TYPE>
		TYPE* Scheduler::ThreadContext::GetUserData() const
		{
			return reinterpret_cast<TYPE*>(mpUserData);
		}
	}
}
