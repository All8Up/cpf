//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Events/Event.hpp"
#include "Events/Emitter.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;
	}

	struct iApplicationMain;
	struct iInputManager;

	struct iApplication : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iApplication"_crc64);

		using OnQuit = Events::Event<0, std::function<bool()>, Events::AnyNotEqual<bool, true, true, false> >;

		virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, iApplicationMain*) = 0;
		virtual COM::Result CPF_STDCALL Run() = 0;
		virtual COM::Result CPF_STDCALL Shutdown() = 0;

		virtual Plugin::iRegistry* CPF_STDCALL GetRegistry() = 0;
		virtual Events::Emitter* CPF_STDCALL GetEmitter() = 0;
	};
}
