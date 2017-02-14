//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/Application.hpp"
#include "sdl2/SDL.h"
#include "Pair.hpp"


namespace Cpf
{
	namespace Adapters
	{
		class WindowedApp : public WindowedApplication
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			WindowedApp();
			~WindowedApp();

			bool Poll() override;
			bool Wait() override;

			bool Create(const WindowDesc& desc, iWindow**) override;

			void AddRawInputHook(RawInputHook, void* userContext) override;
			void RemoveRawInputHook(RawInputHook) override;

		private:
			void _HandleEvent(SDL_Event& event);
			using HookPair = Pair<RawInputHook, void*>;
			using HookVector = Vector<HookPair>;
			HookVector mInputHooks;
		};
	}
}
