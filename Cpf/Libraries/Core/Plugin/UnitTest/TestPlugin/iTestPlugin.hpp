//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin.hpp"

namespace Cpf
{
	struct iTestPlugin : public iUnknown
	{
		static constexpr InterfaceID kIID = InterfaceID("iTestPlugin"_crc64);

		virtual uint32_t Test() = 0;
	};
}
