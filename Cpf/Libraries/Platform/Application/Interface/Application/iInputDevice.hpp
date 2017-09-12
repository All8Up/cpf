//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace CPF
{
	struct iInputDevice : GOM::iUnknown
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iInputDevice"_crc64);
	};
}
