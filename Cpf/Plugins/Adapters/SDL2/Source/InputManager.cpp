//////////////////////////////////////////////////////////////////////////
#include "InputManager.hpp"
#include "Application/iMouseDevice.hpp"
#include "Application/iKeyboardDevice.hpp"
#include "SDL2/CIDs.hpp"
#include "SDL2.hpp"

using namespace Cpf;
using namespace SDL2;

InputManager::InputManager(COM::iUnknown*)
{
	g_Context.GetRegistry()->Create(nullptr, kMouseDeviceCID, iMouseDevice::kIID, mpMouse.AsVoidPP());
	g_Context.GetRegistry()->Create(nullptr, kKeyboardDeviceCID, iKeyboardDevice::kIID, mpKeyboard.AsVoidPP());
}

InputManager::~InputManager()
{}

COM::Result CPF_STDCALL InputManager::QueryInterface(COM::InterfaceID iid, void** outIface)
{
	if (outIface)
	{
		switch (iid.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iInputManager::kIID.GetID():
			*outIface = static_cast<iInputManager*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

Events::Emitter* CPF_STDCALL InputManager::GetEmiter()
{
	return &mEmitter;
}

COM::Result CPF_STDCALL InputManager::EnumerateDevices(EnumCallback, void*)
{
	return COM::kNotImplemented;
}

COM::Result CPF_STDCALL InputManager::GetDevice(COM::InstanceID id, COM::InterfaceID iid, void** outIface)
{
	switch (id.GetID())
	{
	case iMouseDevice::kDefault.GetID():
		return mpMouse->QueryInterface(iid, outIface);
	case iKeyboardDevice::kDefault.GetID():
		return mpKeyboard->QueryInterface(iid, outIface);
	default:
		// TODO: Should this have a custom kUnknownInstance result?  Probably
		break;
	}
	return COM::kError;
}
