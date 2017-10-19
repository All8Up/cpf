//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputManager.hpp"

namespace CPF
{
	struct iMouseDevice;
	struct iKeyboardDevice;

	namespace SDL2
	{
		class InputManager : public tRefCounted<iInputManager>
		{
		public:
			InputManager(Plugin::iRegistry*, GOM::iUnknown*);
			virtual ~InputManager();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t, void**) override;

			GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy) override;

			Events::Emitter* CPF_STDCALL GetEmiter() override;
			GOM::Result CPF_STDCALL EnumerateDevices(EnumCallback, void*) override;
			GOM::Result CPF_STDCALL GetDevice(uint64_t, uint64_t, void**) override;

		private:
			Events::Emitter mEmitter;
			IntrusivePtr<iMouseDevice> mpMouse;
			IntrusivePtr<iKeyboardDevice> mpKeyboard;
		};
	}
}
