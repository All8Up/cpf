//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Tools
	{
		// TODO: Insert a generic script component before this.
		static constexpr GOM::ClassID kPython3CID = GOM::ClassID("Cpf::Tools::iPython3"_crc64);
		struct iPython3 : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Tools::iPython3"_crc64);

			virtual GOM::Result CPF_STDCALL Initialize(const char* basePath) = 0;
			virtual GOM::Result CPF_STDCALL Shutdown() = 0;
		};
	}
}
