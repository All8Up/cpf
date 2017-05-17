//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputDevice.hpp"

namespace Cpf
{
	enum class MouseButton : int32_t;

	struct iMouseDevice : iInputDevice
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iMouseDevice"_crc64);
		static constexpr GOM::InstanceID kDefault = GOM::InstanceID("Cpf::iMouseDevice::kDefault"_crc64);

		virtual GOM::Result CPF_STDCALL GetButtonState(MouseButton*) = 0;
		virtual GOM::Result CPF_STDCALL GetPosition(int32_t*, int32_t*) = 0;
	};
}
