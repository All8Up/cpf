//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/Application.hpp"
#include "Application/iWindow.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	struct WindowDesc;

	struct iWindowedApplication : iApplication
	{
		virtual bool CPF_STDCALL IsRunning() = 0;
		virtual void CPF_STDCALL Quit() = 0;
		virtual COM::Result CPF_STDCALL Poll() = 0;
		virtual COM::Result CPF_STDCALL Wait() = 0;
		virtual COM::Result CPF_STDCALL Create(const WindowDesc&, iWindow**) = 0;
	};
}
