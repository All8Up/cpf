//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/iScheduler.hpp"
#include "Plugin/iRegistry.hpp"

namespace Cpf
{
	static constexpr GOM::ClassID kThreadPoolCID = GOM::ClassID("Cpf::iThreadPool"_crc64);

	struct iThreadPool : GOM::iBase
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iThreadPool"_crc64);

		virtual bool CPF_STDCALL Initialize(Plugin::iRegistry* regy, int threadCount) = 0;
		virtual void CPF_STDCALL Shutdown() = 0;

		virtual void CPF_STDCALL Enqueue(Concurrency::WorkFunction, void* context) = 0;

		virtual int CPF_STDCALL GetAvailableThreads() = 0;
		virtual void CPF_STDCALL SetActiveThreads(int count) = 0;
		virtual int CPF_STDCALL GetActiveThreads() = 0;

		virtual Concurrency::iScheduler* CPF_STDCALL GetScheduler() = 0;
	};
}
