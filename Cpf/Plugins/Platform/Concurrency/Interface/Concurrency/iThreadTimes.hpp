//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/iFence.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		struct ThreadTimeInfo;

		static constexpr COM::ClassID kThreadTimeCID = COM::ClassID("Cpf::Concurrency::iThreadTimes"_crc64);
		struct iThreadTimes : iFence
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Concurrency::iThreadTimes"_crc64);

			virtual void CPF_STDCALL GetTimes(ThreadTimeInfo*) = 0;
		};
	}
}
