//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	struct iInputDevice : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iInputDevice"_crc64);
	};
}
