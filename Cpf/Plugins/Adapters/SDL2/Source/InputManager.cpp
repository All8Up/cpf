//////////////////////////////////////////////////////////////////////////
#include "InputManager.hpp"
#include "CPF/Application/iMouseDevice.hpp"
#include "CPF/Application/iKeyboardDevice.hpp"
#include "SDL2/CIDs.hpp"
#include "SDL2.hpp"
#include "CPF/Plugin/iRegistry.hpp"

using namespace CPF;
using namespace SDL2;

InputManager::InputManager(Plugin::iRegistry*, GOM::iUnknown*)
{
}

InputManager::~InputManager()
{}

GOM::Result CPF_STDCALL InputManager::QueryInterface(uint64_t iid, void** outIface)
{
	if (outIface)
	{
		switch (iid)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iInputManager::kIID.GetID():
			*outIface = static_cast<iInputManager*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL InputManager::Initialize(Plugin::iRegistry* regy)
{
	if (GOM::Succeeded(regy->Create(nullptr, kMouseDeviceCID.GetID(), iMouseDevice::kIID.GetID(), mpMouse.AsVoidPP())) &&
		GOM::Succeeded(regy->Create(nullptr, kKeyboardDeviceCID.GetID(), iKeyboardDevice::kIID.GetID(), mpKeyboard.AsVoidPP())))
	{
		return GOM::kOK;
	}
	return GOM::kError;
}

Events::Emitter* CPF_STDCALL InputManager::GetEmiter()
{
	return &mEmitter;
}

GOM::Result CPF_STDCALL InputManager::EnumerateDevices(EnumCallback, void*)
{
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL InputManager::GetDevice(uint64_t id, uint64_t iid, void** outIface)
{
	switch (id)
	{
	case iMouseDevice::kDefault.GetID():
		return mpMouse->QueryInterface(iid, outIface);
	case iKeyboardDevice::kDefault.GetID():
		return mpKeyboard->QueryInterface(iid, outIface);
	default:
		// TODO: Should this have a custom kUnknownInstance result?  Probably
		break;
	}
	return GOM::kError;
}
