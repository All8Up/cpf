//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/iFence.hpp"

namespace CPF
{
	namespace Concurrency
	{
		struct ThreadTimeInfo;

		static constexpr GOM::ClassID kThreadTimeCID = GOM::ClassID("Cpf::Concurrency::iThreadTimes"_crc64);
		struct iThreadTimes : iFence
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Concurrency::iThreadTimes"_crc64);

			virtual void CPF_STDCALL GetTimes(ThreadTimeInfo*) = 0;
		};
	}
}
