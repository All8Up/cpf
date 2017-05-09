//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr COM::ClassID kFenceCID = COM::ClassID("Cpf::Concurrency::iFence"_crc64);
		struct iFence : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Concurrency::iFence"_crc64);

			virtual void CPF_STDCALL Wait() = 0;
			virtual void CPF_STDCALL Signal() = 0;
		};
	}
}
