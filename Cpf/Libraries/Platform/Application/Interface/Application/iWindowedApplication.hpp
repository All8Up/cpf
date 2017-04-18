//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplication.hpp"
#include "Application/iWindow.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	struct WindowDesc;

	struct iWindowedApplication : iApplication
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iWindowedApplication"_crc64);

		virtual bool CPF_STDCALL IsRunning() = 0;
		virtual void CPF_STDCALL Quit() = 0;
		virtual COM::Result CPF_STDCALL Poll() = 0;
		virtual COM::Result CPF_STDCALL Wait() = 0;
		virtual COM::Result CPF_STDCALL Create(const WindowDesc&, iWindow**) = 0;

		virtual iInputManager* CPF_STDCALL GetInputManager() = 0;
	};
}
