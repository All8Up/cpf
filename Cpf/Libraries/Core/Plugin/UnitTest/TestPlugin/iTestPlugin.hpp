//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin.hpp"

namespace Cpf
{
	static constexpr COM::ClassID kTestPluginCID = COM::ClassID("TestPlugin"_crc64);

	struct iTestPlugin : public COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("iTestPlugin"_crc64);

		virtual uint32_t Test() = 0;
	};
}
