//////////////////////////////////////////////////////////////////////////
#include "InputManager.hpp"
#include "Application/iMouseDevice.hpp"
#include "Application/iKeyboardDevice.hpp"
#include "SDL2/CIDs.hpp"
#include "SDL2.hpp"

using namespace Cpf;
using namespace SDL2;

InputManager::InputManager(GOM::iBase*)
{
	g_Context.GetRegistry()->Create(nullptr, kMouseDeviceCID.GetID(), iMouseDevice::kIID.GetID(), mpMouse.AsVoidPP());
	g_Context.GetRegistry()->Create(nullptr, kKeyboardDeviceCID.GetID(), iKeyboardDevice::kIID.GetID(), mpKeyboard.AsVoidPP());
}

InputManager::~InputManager()
{}

GOM::Result CPF_STDCALL InputManager::Cast(uint64_t iid, void** outIface)
{
	if (outIface)
	{
		switch (iid)
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
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
		return mpMouse->Cast(iid, outIface);
	case iKeyboardDevice::kDefault.GetID():
		return mpKeyboard->Cast(iid, outIface);
	default:
		// TODO: Should this have a custom kUnknownInstance result?  Probably
		break;
	}
	return GOM::kError;
}
