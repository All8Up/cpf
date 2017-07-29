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
			WindowedApp(iUnknown*);
			~WindowedApp();

			//
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			// Overrides for iApplication.
			GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, iApplicationMain*) override;
			GOM::Result CPF_STDCALL Run() override;
			GOM::Result CPF_STDCALL Shutdown() override;

			Plugin::iRegistry* CPF_STDCALL GetRegistry() override;
			Events::Emitter* CPF_STDCALL GetEmitter() override;

			// Overrides for iWindowedApplication.
			bool CPF_STDCALL IsRunning() override;
			void CPF_STDCALL Quit() override;
			GOM::Result CPF_STDCALL Poll() override;
			GOM::Result CPF_STDCALL Wait() override;
			GOM::Result CPF_STDCALL Create(const WindowDesc*, iWindow**) override;
			iInputManager* CPF_STDCALL GetInputManager() override;

		private:
			void _HandleEvent(SDL_Event& event);
			bool mRunning;
			iApplicationMain* mpApplicationMain;
			Plugin::iRegistry* mpRegistry;
			Events::Emitter mEmitter;
			IntrusivePtr<iInputManager> mpInputManager;
		};
	}
}
