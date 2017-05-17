//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;
	}
}

namespace Cpf
{
	namespace Resources
	{
		struct iLocator;

		static constexpr GOM::ClassID kConfigurationCID = GOM::ClassID("Cpf::Resources::iConfiguration"_crc64);
		struct iConfiguration : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iConfiguration"_crc64);

			virtual GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, const char* filename) = 0;
			virtual iLocator* CPF_STDCALL GetLocator() = 0;
		};
	}
}
