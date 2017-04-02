//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		static constexpr COM::ClassID kTimerCID = COM::ClassID("TimerClass"_crc64);

		struct iTimer : iSystem
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iTimer"_crc64);

			virtual Time::Value CPF_STDCALL GetTime() const = 0;
			virtual float CPF_STDCALL GetDeltaTime() const = 0;
			virtual bool CPF_STDCALL IsPaused() const = 0;
			virtual void CPF_STDCALL SetPause(bool flag) = 0;
			virtual void CPF_STDCALL Pause() = 0;
			virtual void CPF_STDCALL Resume() = 0;
		};
	}
}
