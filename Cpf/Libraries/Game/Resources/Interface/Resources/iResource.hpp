//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Resources
	{
		struct iCache;
		struct ID;

		static constexpr COM::ClassID kResourceCID = COM::ClassID("Cpf::Resources::iResource"_crc64);
		struct iResource : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iResource"_crc64);

			virtual void CPF_STDCALL Initialize(ID, iCache*) = 0;
			virtual void CPF_STDCALL Update() = 0;
		};
	}
}
