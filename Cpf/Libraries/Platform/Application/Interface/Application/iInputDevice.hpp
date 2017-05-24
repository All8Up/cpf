//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	struct iInputDevice : GOM::iBase
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iInputDevice"_crc64);
	};
}
