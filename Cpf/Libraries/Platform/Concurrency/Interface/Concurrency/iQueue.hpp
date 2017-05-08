//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		class ThreadContext;

		static constexpr COM::ClassID kQueueCID = COM::ClassID("Cpf::Concurrency::iQueue"_crc64);

		struct iQueue : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Concurrency::iQueue"_crc64);

			/*
			using Payload = void(*)(ThreadContext&, void*);

			virtual COM::Result CPF_STDCALL Reserve(int32_t size) = 0;

			virtual void CPF_STDCALL FirstOne(Payload func, void* context) = 0;
			virtual void CPF_STDCALL FirstOneBarrier(Payload func, void* context) = 0;
			virtual void CPF_STDCALL LastOne(Payload func, void* context) = 0;
			virtual void CPF_STDCALL LastOneBarrier(Payload func, void* context) = 0;
			virtual void CPF_STDCALL All(Payload func, void* context) = 0;
			virtual void CPF_STDCALL AllBarrier(Payload func, void* context) = 0;

			virtual void CPF_STDCALL Barrier() = 0;
			virtual void CPF_STDCALL Fence(Payload func, void* context) = 0;
			*/
		};
	}
}
