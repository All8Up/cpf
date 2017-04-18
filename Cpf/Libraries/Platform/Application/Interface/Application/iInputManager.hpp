//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Events/Emitter.hpp"

namespace Cpf
{
	struct iInputDevice;

	struct iInputManager : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iInputManager"_crc64);

		using OnDeviceAttached = Events::Event<"OnDeviceAttached"_crc32, std::function<void()>>;
		using OnDeviceDetached = Events::Event<"OnDeviceDetached"_crc32, std::function<void()>>;

		using EnumCallback = bool(*)(void*, iInputDevice*);

		virtual Events::Emitter* CPF_STDCALL GetEmiter() = 0;
		virtual COM::Result CPF_STDCALL EnumerateDevices(EnumCallback, void*) = 0;
		virtual COM::Result CPF_STDCALL GetDevice(COM::InstanceID, COM::InterfaceID, void**) = 0;
	};
}
