//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Desktop/iMouseDevice.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace SDL2
	{
		class MouseDevice : public GOM::tUnknown<Platform::Desktop::iMouseDevice>
		{
		public:
			MouseDevice(Plugin::iRegistry*, GOM::iUnknown*);
			virtual ~MouseDevice();

			GOM::Result CPF_STDCALL GetButtonState(Platform::Desktop::MouseButton*) override;
			GOM::Result CPF_STDCALL GetPosition(int32_t*, int32_t*) override;
		};
	}
}
