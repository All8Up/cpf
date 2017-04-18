//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iMouseDevice.hpp"

namespace Cpf
{
	namespace SDL2
	{
		class MouseDevice : public tRefCounted<iMouseDevice>
		{
		public:
			MouseDevice(COM::iUnknown*);
			virtual ~MouseDevice();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			COM::Result CPF_STDCALL GetButtonState(MouseButton*) override;
			COM::Result CPF_STDCALL GetPosition(int32_t*, int32_t*) override;
		};
	}
}
