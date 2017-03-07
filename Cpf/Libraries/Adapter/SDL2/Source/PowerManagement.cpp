//////////////////////////////////////////////////////////////////////////
#include "Adapter/PowerManagement.hpp"
#include "Logging/Logging.hpp"
#include "SDL_syswm.h"

using namespace Cpf;
using namespace Adapter;

void PowerManagementEvents::Suspending() { Emitter.Emit<OnSuspend>(); }
void PowerManagementEvents::Resuming() { Emitter.Emit<OnResume>(); }


Platform::Events::Emitter PowerManagementEvents::Emitter;


//////////////////////////////////////////////////////////////////////////
BatteryPowerManagementEvents::BatteryPowerManagementEvents()
	: mRunning(true)
{
	CPF_INIT_LOG(PowerManagement);
	TimeInitializer::Install();
	Start();
}
BatteryPowerManagementEvents::~BatteryPowerManagementEvents()
{
	TimeInitializer::Remove();
}

void BatteryPowerManagementEvents::Start()
{
	mWorker(std::bind(&BatteryPowerManagementEvents::Worker, this));
}

void BatteryPowerManagementEvents::Worker()
{
	while (mRunning)
	{
		int secs;
		int perc;
		SDL_PowerState state = SDL_GetPowerInfo(&secs, &perc);
		if (state != mLastState)
		{
			CPF_LOG(PowerManagement, Info) << "Power state changed.";
			switch (state)
			{
			case SDL_POWERSTATE_UNKNOWN:
			case SDL_POWERSTATE_NO_BATTERY:
				break;
			case SDL_POWERSTATE_ON_BATTERY:
				Emitter.Emit<OnUnplugged>(Time::Value(Time::Seconds(float(secs))), float(perc) / float(100));
				break;
			case SDL_POWERSTATE_CHARGING:
				Emitter.Emit<OnCharging>(Time::Value(Time::Seconds(float(secs))), float(perc) / float(100));
				break;
			case SDL_POWERSTATE_CHARGED:
				Emitter.Emit<OnCharged>();
				break;
			}
			mLastState = state;
		}
		else
		{
			switch (state)
			{
			case SDL_POWERSTATE_UNKNOWN:
			case SDL_POWERSTATE_NO_BATTERY:
				break;
			case SDL_POWERSTATE_ON_BATTERY:
				CPF_LOG(PowerManagement, Info) << "On battery: " << secs << " - " << perc << "%";
				Emitter.Emit<OnUnplugged>(Time::Value(Time::Seconds(float(secs))), perc / float(100));
				break;
			case SDL_POWERSTATE_CHARGING:
				CPF_LOG(PowerManagement, Info) << "Charging: " << secs << " - " << perc << "%";
				Emitter.Emit<OnCharging>(Time::Value(Time::Seconds(float(secs))), perc / float(100));
				break;
			case SDL_POWERSTATE_CHARGED:
				CPF_LOG(PowerManagement, Info) << "Charged.";
				break;
			}
		}

		Threading::Thread::Sleep(Time::Seconds(30));
	}
}
