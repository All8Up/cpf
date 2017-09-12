//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplication.hpp"
#include "Application/iWindow.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	struct WindowDesc;

	struct iWindowedApplication : iApplication
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iWindowedApplication"_crc64);

		/**
		 * @brief Determine if the application is supposed to still be running.
		 * @return True if the application is still running, false if a quit request has been made.
		 */
		virtual bool CPF_STDCALL IsRunning() = 0;

		/**
		 * @brief Issues a quit request.
		 */
		virtual void CPF_STDCALL Quit() = 0;

		/**
		 * @brief Polls the application for events.
		 * @return A result code.
		 */
		virtual GOM::Result CPF_STDCALL Poll() = 0;

		/**
		 * @brief Waits for an application event.
		 * @return A result code.
		 */
		virtual GOM::Result CPF_STDCALL Wait() = 0;

		/**
		 * @brief Creates a new CPF_STDCALL.
		 * @param desc The window descriptor.
		 * @param [in,out] outWindow The window output variable.
		 * @return A result code.
		 */
		virtual GOM::Result CPF_STDCALL Create(const WindowDesc* desc, iWindow** outWindow) = 0;

		/**
		 * @brief Gets input manager.
		 * @return The input manager.
		 */
		virtual iInputManager* CPF_STDCALL GetInputManager() = 0;
	};
}
