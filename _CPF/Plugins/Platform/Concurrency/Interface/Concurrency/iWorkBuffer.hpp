//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/iScheduler.hpp"

namespace CPF
{
	namespace Concurrency
	{
		class ThreadContext;

		static constexpr GOM::ClassID kWorkBufferCID = GOM::ClassID("Cpf::Concurrency::iWorkBuffer"_crc64);

		struct iWorkBuffer : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Concurrency::iWorkBuffer"_crc64);

			virtual GOM::Result CPF_STDCALL Reserve(int32_t size) = 0;
			virtual void CPF_STDCALL Copy(iWorkBuffer*) = 0;

			virtual void CPF_STDCALL Reset() = 0;

			virtual void CPF_STDCALL FirstOne(WorkFunction func, void* context) = 0;
			virtual void CPF_STDCALL FirstOneBarrier(WorkFunction func, void* context) = 0;
			virtual void CPF_STDCALL LastOne(WorkFunction func, void* context) = 0;
			virtual void CPF_STDCALL LastOneBarrier(WorkFunction func, void* context) = 0;
			virtual void CPF_STDCALL All(WorkFunction func, void* context) = 0;
			virtual void CPF_STDCALL AllBarrier(WorkFunction func, void* context) = 0;

			virtual void CPF_STDCALL Barrier() = 0;
			virtual void CPF_STDCALL Fence(WorkFunction func, void* context) = 0;
		};
	}
}
