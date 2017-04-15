//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/Application.hpp"
#include "Application/iWindow.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	struct WindowDesc;

	//////////////////////////////////////////////////////////////////////////
	class WindowedApplication : public Application
	{
	public:
		virtual bool Poll() = 0;
		virtual bool Wait() = 0;

		virtual bool Create(const WindowDesc&, iWindow**) = 0;

		using RawInputHook = bool(*)(void* userContext, const void* event);
		virtual void AddRawInputHook(RawInputHook, void* userContext) = 0;
		virtual void RemoveRawInputHook(RawInputHook) = 0;
	};
}
