//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Platform/Threading/Thread.hpp"
#include "Concurrency/ThreadContext.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr COM::ClassID kSchedulerCID = COM::ClassID("Cpf::iScheduler"_crc64);

		using PayloadFunc_t = void(*)(ThreadContext&, void*);

		struct iScheduler : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iScheduler"_crc64);

			virtual bool CPF_STDCALL Initialize(Threading::Thread::Group&&) = 0;
			virtual void CPF_STDCALL Shutdown() = 0;
		};
	}
}
