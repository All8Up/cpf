//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iKeyboardDevice.hpp"

namespace Cpf
{
	namespace SDL2
	{
		class KeyboardDevice : public tRefCounted<iKeyboardDevice>
		{
		public:
			KeyboardDevice(COM::iUnknown*);
			virtual ~KeyboardDevice();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			COM::Result CPF_STDCALL GetModifiers(KeyModifier*) override;
		};
	}
}
