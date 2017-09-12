//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace CPF
{
	namespace Concurrency
	{
		static constexpr GOM::ClassID kLoadBalancerCID = GOM::ClassID("Cpf::Concurrency::iLoadBalancer"_crc64);
		struct iLoadBalancer : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Concurrency::iLoadBalancer"_crc64);

			virtual GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, int count, iScheduler**) = 0;
			virtual void CPF_STDCALL Balance() = 0;
		};
	}
}
