//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}
	struct iApplication;

	struct iApplicationMain : GOM::iUnknown
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iApplicationMain"_crc64);

		using AppMainCreate = iApplicationMain* (*)();

		virtual GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, GOM::ClassID* appCid) = 0;
		virtual GOM::Result CPF_STDCALL Main(iApplication*) = 0;
		virtual void CPF_STDCALL Shutdown() = 0;
	};
}

#define CPF_CREATE_APPMAIN(appName)												\
namespace { CPF::iApplicationMain* CreateAppMain() { return new appName; } }	\
CPF::iApplicationMain::AppMainCreate gs_AppMainCreate = CreateAppMain;
