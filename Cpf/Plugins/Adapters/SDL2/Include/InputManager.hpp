//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputManager.hpp"

namespace Cpf
{
	struct iMouseDevice;
	struct iKeyboardDevice;

	namespace SDL2
	{
		class InputManager : public tRefCounted<iInputManager>
		{
		public:
			InputManager(COM::iUnknown*);
			virtual ~InputManager();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override;

			Events::Emitter* CPF_STDCALL GetEmiter() override;
			COM::Result CPF_STDCALL EnumerateDevices(EnumCallback, void*) override;
			COM::Result CPF_STDCALL GetDevice(COM::InstanceID, COM::InterfaceID, void**) override;

		private:
			Events::Emitter mEmitter;
			IntrusivePtr<iMouseDevice> mpMouse;
			IntrusivePtr<iKeyboardDevice> mpKeyboard;
		};
	}
}
