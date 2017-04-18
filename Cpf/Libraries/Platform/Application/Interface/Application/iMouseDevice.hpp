//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputDevice.hpp"

namespace Cpf
{
	enum class MouseButton : int32_t;

	struct iMouseDevice : iInputDevice
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iMouseDevice"_crc64);
		static constexpr COM::InstanceID kDefault = COM::InstanceID("Cpf::iMouseDevice::kDefault"_crc64);

		virtual COM::Result CPF_STDCALL GetButtonState(MouseButton*) = 0;
		virtual COM::Result CPF_STDCALL GetPosition(int32_t*, int32_t*) = 0;
	};
}
