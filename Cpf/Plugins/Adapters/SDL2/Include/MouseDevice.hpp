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
			MouseDevice(GOM::iBase*);
			virtual ~MouseDevice();

			GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void** outIface) override;

			GOM::Result CPF_STDCALL GetButtonState(MouseButton*) override;
			GOM::Result CPF_STDCALL GetPosition(int32_t*, int32_t*) override;
		};
	}
}
