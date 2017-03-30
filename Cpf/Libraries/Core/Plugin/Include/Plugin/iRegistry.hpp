//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct CPF_EXPORT iRegistry : iUnknown
		{
			static constexpr InterfaceID kIID = InterfaceID("iRegistry"_crc64);

			using Creator = void*(*)(iUnknown*);

			virtual bool CPF_STDCALL Load(const char* const) = 0;
			virtual bool CPF_STDCALL Install(InterfaceID, Creator) = 0;
			virtual bool CPF_STDCALL Remove(InterfaceID) = 0;
			virtual bool CPF_STDCALL Exists(InterfaceID) = 0;
			virtual bool CPF_STDCALL Create(iUnknown*, InterfaceID, void**) = 0;
		};
	}
}
