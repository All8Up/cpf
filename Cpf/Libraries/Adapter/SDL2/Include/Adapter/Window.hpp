//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SDL.h"
#include "WindowedApp.hpp"


namespace Cpf
{
	namespace Adapter
	{
		static constexpr COM::ClassID kSDL2WindowCID = COM::ClassID("SDL2 Window"_crc64);

		class Window : public iWindow
		{
		public:
			Window();
			virtual ~Window();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			bool Initialize(SDL_Window* win);

			Math::Vector2i GetClientArea() const override;
			OSWindowData GetOSWindowData() const override;
			Events::Emitter& GetEmitter() override { return mEmitter; }

			SDL_Window* GetSDLWindow() const;
		private:
			SDL_Window* mpWindow;
			Events::Emitter mEmitter;
		};
	}
}
