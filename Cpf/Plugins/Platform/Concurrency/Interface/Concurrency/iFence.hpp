//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr GOM::ClassID kFenceCID = GOM::ClassID("Cpf::Concurrency::iFence"_crc64);
		struct iFence : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Concurrency::iFence"_crc64);

			virtual void CPF_STDCALL Wait() = 0;
			virtual void CPF_STDCALL Signal() = 0;
		};
	}
}
