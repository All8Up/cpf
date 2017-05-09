//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/iScheduler.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		class ThreadContext;

		static constexpr COM::ClassID kWorkBufferCID = COM::ClassID("Cpf::Concurrency::iWorkBuffer"_crc64);

		struct iWorkBuffer : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Concurrency::iWorkBuffer"_crc64);

			virtual COM::Result CPF_STDCALL Reserve(int32_t size) = 0;
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
