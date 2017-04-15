//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SDL.h"
#include "WindowedApp.hpp"


namespace Cpf
{
	namespace Adapter
	{
		static constexpr COM::ClassID kSDL2WindowCID = COM::ClassID("SDL2 Window"_crc64);

		class Window : public tRefCounted<iWindow>
		{
		public:
			Window();
			virtual ~Window();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			bool Initialize(SDL_Window* win);

			void CPF_STDCALL SetTitle(const char* title) override;
			void CPF_STDCALL SetPosition(int32_t, int32_t) override;
			void CPF_STDCALL GetPosition(int32_t*, int32_t*) override;
			void CPF_STDCALL SetSize(int32_t, int32_t) override;
			void CPF_STDCALL GetSize(int32_t*, int32_t*) override;
			void CPF_STDCALL Minimize() override;
			void CPF_STDCALL Maximize() override;
			void CPF_STDCALL Restore() override;
			COM::Result CPF_STDCALL GetClientAreaSize(int32_t* w, int32_t* h) override;
			COM::Result CPF_STDCALL GetOSData(OSWindowData*) override;
			Events::Emitter* CPF_STDCALL GetEmitter() override { return &mEmitter; }

			SDL_Window* GetSDLWindow() const;
		private:
			SDL_Window* mpWindow;
			Events::Emitter mEmitter;
		};
	}
}
