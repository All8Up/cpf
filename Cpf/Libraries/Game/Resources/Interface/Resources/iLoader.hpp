//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"


namespace Cpf
{
	namespace Resources
	{
		struct ID;
		struct iLocator;
		struct iResource;

		struct iLoader : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iLoader"_crc64);

			virtual uint32_t CPF_STDCALL GetID() = 0;
			virtual iResource* CPF_STDCALL GetResource(ID id) = 0;
		};
	}
}
