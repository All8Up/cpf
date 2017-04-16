//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Application/Arguments.hpp"
#include "Events/Emitter.hpp"
#include "Math/Vector2v.hpp"
#include "String.hpp"
#include "PluginHost/Registry.hpp"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	struct iApplication;

	struct iApplicationMain : COM::iUnknown
	{
		using AppMainCreate = iApplicationMain* (*)();

		virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, COM::ClassID* appCid) = 0;
		virtual COM::Result CPF_STDCALL Main(iApplication*) = 0;
		virtual void CPF_STDCALL Shutdown() = 0;
	};

	struct iApplication : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iApplication"_crc64);

		using OnQuit = Events::Event< 0, std::function< bool() >, Events::AnyNotEqual<bool, true, true, false> >;

		virtual COM::Result CPF_STDCALL Initialize(iApplicationMain*) = 0;
		virtual COM::Result CPF_STDCALL Run() = 0;
		virtual COM::Result CPF_STDCALL Shutdown() = 0;

		virtual Plugin::iRegistry* CPF_STDCALL GetRegistry() = 0;
		virtual Events::Emitter* CPF_STDCALL GetEmitter() = 0;
	};
}


#define CPF_CREATE_APPMAIN(appName)												\
namespace { Cpf::iApplicationMain* CreateAppMain() { return new appName; } }	\
Cpf::iApplicationMain::AppMainCreate gs_AppMainCreate = CreateAppMain;
