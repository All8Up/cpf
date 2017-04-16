//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;
	}
	struct iApplication;

	struct iApplicationMain : COM::iUnknown
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iApplicationMain"_crc64);

		using AppMainCreate = iApplicationMain* (*)();

		virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, COM::ClassID* appCid) = 0;
		virtual COM::Result CPF_STDCALL Main(iApplication*) = 0;
		virtual void CPF_STDCALL Shutdown() = 0;
	};
}

#define CPF_CREATE_APPMAIN(appName)												\
namespace { Cpf::iApplicationMain* CreateAppMain() { return new appName; } }	\
Cpf::iApplicationMain::AppMainCreate gs_AppMainCreate = CreateAppMain;
