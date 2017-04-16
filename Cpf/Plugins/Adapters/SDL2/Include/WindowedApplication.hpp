//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iWindowedApplication.hpp"
#include "SDL.h"
#include "Pair.hpp"


namespace Cpf
{
	namespace SDL2
	{
		class WindowedApp : public tRefCounted<iWindowedApplication>
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			WindowedApp(COM::iUnknown*);
			~WindowedApp();

			//
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			// Overrides for iApplication.
			COM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, iApplicationMain*) override;
			COM::Result CPF_STDCALL Run() override;
			COM::Result CPF_STDCALL Shutdown() override;

			Plugin::iRegistry* CPF_STDCALL GetRegistry() override;
			Events::Emitter* CPF_STDCALL GetEmitter() override;

			// Overrides for iWindowedApplication.
			bool CPF_STDCALL IsRunning() override;
			void CPF_STDCALL Quit() override;
			COM::Result CPF_STDCALL Poll() override;
			COM::Result CPF_STDCALL Wait() override;
			COM::Result CPF_STDCALL Create(const WindowDesc&, iWindow**) override;

		private:
			void _HandleEvent(SDL_Event& event);
			bool mRunning;
			iApplicationMain* mpApplicationMain;
			Plugin::iRegistry* mpRegistry;
			Events::Emitter mEmitter;
		};
	}
}
