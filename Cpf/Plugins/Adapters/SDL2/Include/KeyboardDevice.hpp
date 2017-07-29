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
			KeyboardDevice(GOM::iUnknown*);
			virtual ~KeyboardDevice();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL GetModifiers(KeyModifier*) override;
		};
	}
}
