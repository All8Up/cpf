//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputDevice.hpp"

namespace CPF
{
	enum class KeyModifier : int32_t;

	struct iKeyboardDevice : iInputDevice
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iKeyboardDevice"_crc64);
		static constexpr GOM::InstanceID kDefault = GOM::InstanceID("Cpf::iKeyboardDevice::Default"_crc64);

		/**
		 * @brief Gets the modifier keys currently set.
		 * @param [in,out] modifiers The output to the modifier value.
		 * @return The result code.
		 */
		virtual GOM::Result CPF_STDCALL GetModifiers(KeyModifier* modifiers) = 0;
	};
}
