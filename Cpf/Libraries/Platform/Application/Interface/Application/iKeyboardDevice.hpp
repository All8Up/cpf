//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputDevice.hpp"

namespace Cpf
{
	struct iKeyboardDevice : iInputDevice
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iKeyboardDevice"_crc64);
		static constexpr COM::InstanceID kDefault = COM::InstanceID("Cpf::iKeyboardDevice::Default"_crc64);
	};
}
