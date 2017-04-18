//////////////////////////////////////////////////////////////////////////
#include "KeyboardDevice.hpp"
#include "SDL.h"

using namespace Cpf;
using namespace SDL2;


KeyboardDevice::KeyboardDevice(COM::iUnknown*)
{}

KeyboardDevice::~KeyboardDevice()
{}

COM::Result CPF_STDCALL KeyboardDevice::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iInputDevice::kIID.GetID():
			*outIface = static_cast<iInputDevice*>(this);
			break;
		case iKeyboardDevice::kIID.GetID():
			*outIface = static_cast<iKeyboardDevice*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
