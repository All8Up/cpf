//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/WindowedApplication.hpp"
#include "SDL.h"
#include "Pair.hpp"


namespace Cpf
{
	namespace Adapter
	{
		class WindowedApp : public iWindowedApplication
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			WindowedApp();
			~WindowedApp() override;

			bool Poll() override;
			bool Wait() override;

			bool Create(const WindowDesc& desc, iWindow**) override;

		private:
			void _HandleEvent(SDL_Event& event);
		};
	}
}
