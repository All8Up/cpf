//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr COM::ClassID kSchedulerCID = COM::ClassID("Cpf::iScheduler"_crc64);

		struct WorkContext;
		struct ThreadTimeInfo;
		struct iWorkBuffer;
		struct iFence;
		struct iThreadTimes;

		using WorkFunction = void(*)(const WorkContext*, void*);

		struct iScheduler : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iScheduler"_crc64);

			virtual COM::Result CPF_STDCALL Initialize(int threadCount, WorkFunction init, WorkFunction shutdown, void* context) = 0;
			virtual void CPF_STDCALL Shutdown() = 0;

			virtual int CPF_STDCALL GetMaxThreads() = 0;
			virtual int CPF_STDCALL GetActiveThreads() = 0;
			virtual void CPF_STDCALL SetActiveThreads(int count) = 0;

			virtual void CPF_STDCALL Execute(iWorkBuffer*, bool clear = true) = 0;
			virtual void CPF_STDCALL Submit(iFence*) = 0;
			virtual void CPF_STDCALL Submit(iThreadTimes*) = 0;
		};

		//////////////////////////////////////////////////////////////////////////
		// Helper utility for payload functions.  This is a nasty little thing
		// since it relies on a unique instantiation of the template for each
		// specific member it will call.  The macro wrapper takes care of the unique
		// identifier via the macro counter.  In most cases, the benefits out weight the
		// evil inherent.
		template<typename TYPE, int UNIQUE>
		WorkFunction ThreadedCall(void(TYPE::*function)(const WorkContext*))
		{
			using FunctionType = void(TYPE::*)(const WorkContext*);
			static FunctionType func = function;
			struct Caller
			{
				static void Call(const WorkContext* tc, void* context)
				{
					TYPE* type = reinterpret_cast<TYPE*>(context);
					(type->*func)(tc);
				}
			};
			return &Caller::Call;
		}
#define SCHEDULED_CALL(t, f) Cpf::Concurrency::ThreadedCall<t, __COUNTER__>(f)
	}
}
