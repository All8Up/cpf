//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Resources
	{
		struct ID;
		struct iLocator;

		static constexpr COM::ClassID kMonitorManualCID = COM::ClassID("Cpf::Resources::Monitors::iManual"_crc64);
		static constexpr COM::ClassID kMonitorFileSystemCID = COM::ClassID("Cpf::Resources::Monitors::iFileSystem"_crc64);

		struct iMonitor : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iMonitor"_crc64);

			virtual bool CPF_STDCALL Touch(ID) = 0;
			virtual void CPF_STDCALL TouchAll() = 0;

			virtual void CPF_STDCALL SetLocator(iLocator*) = 0;
			virtual iLocator* CPF_STDCALL GetLocator() const = 0;
		};
	}
}
