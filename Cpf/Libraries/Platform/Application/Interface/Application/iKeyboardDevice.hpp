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

		/**
		 * @brief Gets the modifier keys currently set.
		 * @param [in,out] modifiers The output to the modifier value.
		 * @return The result code.
		 */
		virtual COM::Result CPF_STDCALL GetModifiers(KeyModifier* modifiers) = 0;
	};
}
