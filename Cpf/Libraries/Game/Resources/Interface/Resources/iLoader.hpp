//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"


namespace Cpf
{
	namespace Resources
	{
		struct ID;
		struct iLocator;
		struct iResource;

		struct iLoader : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iLoader"_crc64);

			virtual uint32_t CPF_STDCALL GetID() = 0;
			virtual iResource* CPF_STDCALL GetResource(ID id) = 0;
		};
	}
}
