//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Desktop/iKeyboardDevice.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace SDL2
	{
		class KeyboardDevice : public GOM::tUnknown<Platform::Desktop::iKeyboardDevice>
		{
		public:
			KeyboardDevice();
			virtual ~KeyboardDevice();

			GOM::Result CPF_STDCALL GetModifiers(Platform::Desktop::KeyModifier*) override;
		};
	}
}
