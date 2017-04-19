//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	struct iClipboard : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iClipboard"_crc64);
		static constexpr COM::InstanceID kDefault = COM::InstanceID("Cpf::iClipboard::Default"_crc64);

		virtual COM::Result CPF_STDCALL GetClipboardText(int32_t*, char*) = 0;
		virtual COM::Result CPF_STDCALL SetClipboardText(const char*) = 0;
	};
}
