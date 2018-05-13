//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Desktop/iEventLoop.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "SDL.h"

namespace CPF
{
	namespace SDL2
	{
		class EventLoop : public GOM::tUnknown<Platform::Desktop::iEventLoop>
		{
		public:
			EventLoop(Plugin::iRegistry*, iUnknown*) {}

			GOM::Result CPF_STDCALL Run() override;
			GOM::Result CPF_STDCALL RunOne() override;
			GOM::Result CPF_STDCALL RunAvailable() override;

		private:
			void EventLoop::_HandleEvent(SDL_Event& event);
		};
	}
}
