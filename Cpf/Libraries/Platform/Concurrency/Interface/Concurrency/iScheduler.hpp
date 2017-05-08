//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Concurrency/iQueue.hpp"
#include "Concurrency/WorkContext.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr COM::ClassID kSchedulerCID = COM::ClassID("Cpf::iScheduler"_crc64);

		class Semaphore;

		using WorkFunction = void(*)(const WorkContext*, void*);

		struct iScheduler : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iScheduler"_crc64);

			virtual COM::Result CPF_STDCALL Initialize(int threadCount, WorkFunction init, WorkFunction shutdown, void* context) = 0;
			virtual void CPF_STDCALL Shutdown() = 0;

			virtual int CPF_STDCALL GetMaxThreads() = 0;
			virtual int CPF_STDCALL GetActiveThreads() = 0;

			virtual void CPF_STDCALL Execute(iQueue*, bool clear = true) = 0;
			virtual void Submit(Semaphore*) = 0;
		};
	}
}
