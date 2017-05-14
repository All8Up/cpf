//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Tools
	{
		// TODO: Insert a generic script component before this.
		static constexpr COM::ClassID kPython3CID = COM::ClassID("Cpf::Tools::iPython3"_crc64);
		struct iPython3 : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Tools::iPython3"_crc64);

			virtual COM::Result CPF_STDCALL Initialize(const char* basePath) = 0;
			virtual COM::Result CPF_STDCALL Shutdown() = 0;
		};
	}
}
