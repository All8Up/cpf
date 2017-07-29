//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Resources
	{
		struct ID;
		struct iLocator;

		static constexpr GOM::ClassID kMonitorManualCID = GOM::ClassID("Cpf::Resources::Monitors::iManual"_crc64);
		static constexpr GOM::ClassID kMonitorFileSystemCID = GOM::ClassID("Cpf::Resources::Monitors::iFileSystem"_crc64);

		struct iMonitor : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iMonitor"_crc64);

			virtual bool CPF_STDCALL Touch(ID) = 0;
			virtual void CPF_STDCALL TouchAll() = 0;

			virtual void CPF_STDCALL SetLocator(iLocator*) = 0;
			virtual iLocator* CPF_STDCALL GetLocator() const = 0;
		};
	}
}
