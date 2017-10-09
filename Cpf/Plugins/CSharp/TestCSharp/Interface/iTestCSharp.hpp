//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Plugin.hpp"

namespace CPF
{
	static constexpr GOM::ClassID kTestPluginCID = GOM::ClassID("TestPlugin"_crc64);

	struct iTestPlugin : GOM::iUnknown
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iTestPlugin"_crc64);

		virtual uint32_t Test() = 0;
	};
}
