//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SDL.h"
#include "Application/iWindow.hpp"
#include "Events/Emitter.hpp"

namespace Cpf
{
	namespace SDL2
	{
		class Window : public tRefCounted<iWindow>
		{
		public:
			Window(GOM::iUnknown*);
			virtual ~Window();

			GOM::Result CPF_STDCALL QueryInterface(GOM::InterfaceID id, void** outIface) override;

			bool CPF_STDCALL Initialize(const WindowDesc* desc) override;
			void CPF_STDCALL SetTitle(const char* title) override;
			void CPF_STDCALL SetPosition(int32_t, int32_t) override;
			void CPF_STDCALL GetPosition(int32_t*, int32_t*) override;
			void CPF_STDCALL SetSize(int32_t, int32_t) override;
			void CPF_STDCALL GetSize(int32_t*, int32_t*) override;
			void CPF_STDCALL Minimize() override;
			void CPF_STDCALL Maximize() override;
			void CPF_STDCALL Restore() override;
			GOM::Result CPF_STDCALL GetClientAreaSize(int32_t* w, int32_t* h) override;
			GOM::Result CPF_STDCALL GetOSData(OSWindowData*) override;
			Events::Emitter* CPF_STDCALL GetEmitter() override { return &mEmitter; }

			SDL_Window* GetSDLWindow() const;
		private:
			SDL_Window* mpWindow;
			Events::Emitter mEmitter;
		};
	}
}
