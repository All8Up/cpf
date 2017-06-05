//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Testing
{
	static constexpr Cpf::GOM::ClassID kTestCID = Cpf::GOM::ClassID("Testing::iTest"_crc64);

	struct iTest : Cpf::GOM::iBase
	{
		static constexpr Cpf::GOM::InterfaceID kIID = Cpf::GOM::InterfaceID("Testing::iTest"_crc64);

		virtual int32_t CPF_STDCALL Tester(int64_t) = 0;
	};
}
