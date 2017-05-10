//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Resources
	{
		static constexpr COM::ClassID kConfigurationCID = COM::ClassID("Cpf::Resources::iConfiguration"_crc64);
		struct iConfiguration : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iConfiguration"_crc64);

		};
	}
}
