//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
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

	struct iApplication : GOM::iBase
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iApplication"_crc64);

		using OnQuit = Events::Event<0, std::function<bool()>, Events::AnyNotEqual<bool, true, true, false> >;

		virtual GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, iApplicationMain*) = 0;
		virtual GOM::Result CPF_STDCALL Run() = 0;
		virtual GOM::Result CPF_STDCALL Shutdown() = 0;

		virtual Plugin::iRegistry* CPF_STDCALL GetRegistry() = 0;
		virtual Events::Emitter* CPF_STDCALL GetEmitter() = 0;
	};
}
