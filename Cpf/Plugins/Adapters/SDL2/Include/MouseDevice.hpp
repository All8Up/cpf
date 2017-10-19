//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iMouseDevice.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace SDL2
	{
		class MouseDevice : public tRefCounted<iMouseDevice>
		{
		public:
			MouseDevice(Plugin::iRegistry*, GOM::iUnknown*);
			virtual ~MouseDevice();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			GOM::Result CPF_STDCALL GetButtonState(MouseButton*) override;
			GOM::Result CPF_STDCALL GetPosition(int32_t*, int32_t*) override;
		};
	}
}
