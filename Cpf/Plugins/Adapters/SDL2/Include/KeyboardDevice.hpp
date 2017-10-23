//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Application/iKeyboardDevice.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace SDL2
	{
		class KeyboardDevice : public tRefCounted<iKeyboardDevice>
		{
		public:
			KeyboardDevice(Plugin::iRegistry*, GOM::iUnknown*);
			virtual ~KeyboardDevice();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL GetModifiers(KeyModifier*) override;
		};
	}
}
