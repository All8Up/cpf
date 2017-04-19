//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputDevice.hpp"

namespace Cpf
{
	enum class KeyModifier : int32_t;

	struct iKeyboardDevice : iInputDevice
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iKeyboardDevice"_crc64);
		static constexpr COM::InstanceID kDefault = COM::InstanceID("Cpf::iKeyboardDevice::Default"_crc64);

		virtual COM::Result CPF_STDCALL GetModifiers(KeyModifier*) = 0;
	};
}
