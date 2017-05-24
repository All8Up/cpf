//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Resources
	{
		struct iCache;
		struct ID;

		static constexpr GOM::ClassID kResourceCID = GOM::ClassID("Cpf::Resources::iResource"_crc64);
		struct iResource : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Resources::iResource"_crc64);

			virtual void CPF_STDCALL Initialize(ID, iCache*) = 0;
			virtual void CPF_STDCALL Update() = 0;
		};
	}
}
