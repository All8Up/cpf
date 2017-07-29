//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace Tools
	{
		using CreateRegistryPtr = GOM::Result(*)(Plugin::iRegistry**);

		// TODO: Insert a generic script component before this.
		static constexpr GOM::ClassID kPython3CID = GOM::ClassID("Cpf::Tools::iPython3"_crc64);
		struct iPython3 : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Tools::iPython3"_crc64);

			virtual GOM::Result CPF_STDCALL Initialize(const char* basePath, CreateRegistryPtr) = 0;
			virtual GOM::Result CPF_STDCALL Shutdown() = 0;
		};
	}
}
