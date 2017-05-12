//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

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

		static constexpr COM::ClassID kConfigurationCID = COM::ClassID("Cpf::Resources::iConfiguration"_crc64);
		struct iConfiguration : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iConfiguration"_crc64);

			virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, const char* filename) = 0;
			virtual iLocator* CPF_STDCALL GetLocator() = 0;
		};
	}
}
