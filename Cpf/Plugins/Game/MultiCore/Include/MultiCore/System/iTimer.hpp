//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Time/Value.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		static constexpr GOM::ClassID kTimerCID = GOM::ClassID("TimerClass"_crc64);

		/**
		 @brief A game timer system.
		 */
		struct iTimer : iSystem
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iTimer"_crc64);

			/**
			 @brief Gets the time.
			 @return The time.
			 */
			virtual Time::Value CPF_STDCALL GetTime() = 0;

			/**
			 @brief Gets delta time.
			 @return The delta time.
			 */
			virtual float CPF_STDCALL GetDeltaTime() = 0;

			/**
			 @brief Returns if the timer is paused.
			 @return True/false based on state.
			 */
			virtual bool CPF_STDCALL IsPaused() = 0;

			/**
			 @brief Sets the timer pause state.
			 @param flag True to flag.
			 */
			virtual void CPF_STDCALL SetPause(bool flag) = 0;

			/**
			 @brief Pauses the timer.
			 */
			virtual void CPF_STDCALL Pause() = 0;

			/**
			 @brief Resumes the timer.
			 */
			virtual void CPF_STDCALL Resume() = 0;
		};
	}
}
