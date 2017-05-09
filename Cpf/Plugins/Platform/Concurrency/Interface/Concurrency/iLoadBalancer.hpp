//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr COM::ClassID kLoadBalancerCID = COM::ClassID("Cpf::Concurrency::iLoadBalancer"_crc64);
		struct iLoadBalancer : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Concurrency::iLoadBalancer"_crc64);

			virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, int count, iScheduler**) = 0;
			virtual void CPF_STDCALL Balance() = 0;
		};
	}
}
