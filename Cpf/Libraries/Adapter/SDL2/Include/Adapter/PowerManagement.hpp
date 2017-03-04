//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/Application.hpp"
#include "Threading/Thread.hpp"
#include "Time/Value.hpp"
#include "Functional.hpp"
#include "SDL.h"

namespace Cpf
{
	namespace Adapter
	{
		//////////////////////////////////////////////////////////////////////////
		class PowerManagementEvents
		{
		public:
			using OnSuspend = Platform::Events::Event< 1, Function< void() > >;
			using OnResume = Platform::Events::Event< 2, Function< void() > >;

			using OnPluggedIn = Platform::Events::Event< 3, Function< void() > >;
			using OnCharging = Platform::Events::Event< 4, Function< void(Platform::Time::Value, float) > >;
			using OnCharged = Platform::Events::Event< 5, Function< void() > >;
			using OnUnplugged = Platform::Events::Event< 6, Function< void(Platform::Time::Value, float) > >;

			static Platform::Events::Emitter Emitter;

		protected:
			static void Suspending();
			static void Resuming();
		};


		class BatteryPowerManagementEvents : PowerManagementEvents
		{
		public:
			BatteryPowerManagementEvents();
			~BatteryPowerManagementEvents();

			void Start();
			void Worker();

		private:
			volatile bool mRunning;
			Threading::Thread mWorker;
			SDL_PowerState mLastState;
		};

		class Window : public iWindow
		{
		public:
			Window(SDL_Window* win);
			virtual ~Window();

			Math::Vector2i GetClientArea() const override;

#if CPF_TARGET_WINDOWS
			HDC GetHDC() const;
#endif
			SDL_Window* GetSDLWindow() const;
		private:
			SDL_Window* mpWindow;
		};
	}
}
