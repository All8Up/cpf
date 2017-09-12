//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace CPF
{
	namespace Resources
	{
		struct iCache;
		struct ID;

		static constexpr GOM::ClassID kResourceCID = GOM::ClassID("Cpf::Resources::iResource"_crc64);
		struct iResource : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iResource"_crc64);

			virtual void CPF_STDCALL Initialize(ID, iCache*) = 0;
			virtual void CPF_STDCALL Update() = 0;
		};
	}
}
