//////////////////////////////////////////////////////////////////////////
#pragma once
#include "sdl2/SDL.h"
#include "WindowedApp.hpp"


namespace Cpf
{
	namespace Adapters
	{
		class Window : public iWindow
		{
		public:
			Window(SDL_Window* win);
			virtual ~Window();

			Math::Vector2i GetClientArea() const override;
			OSWindowData GetOSWindowData() const override;
			Platform::Events::Emitter& GetEmitter() override { return mEmitter; }

			SDL_Window* GetSDLWindow() const;
		private:
			SDL_Window* mpWindow;
			Platform::Events::Emitter mEmitter;
		};
	}
}
