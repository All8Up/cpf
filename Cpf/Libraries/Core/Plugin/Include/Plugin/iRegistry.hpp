//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct CPF_EXPORT iClassInstance;

		struct CPF_EXPORT iRegistry : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iRegistry"_crc64);

			virtual COM::Result CPF_STDCALL Load(const char* const) = 0;
			virtual COM::Result CPF_STDCALL Install(COM::ClassID cid, iClassInstance* clsInst) = 0;
			virtual COM::Result CPF_STDCALL Remove(COM::ClassID cid) = 0;
			virtual COM::Result CPF_STDCALL Exists(COM::ClassID cid) = 0;
			virtual COM::Result CPF_STDCALL Create(COM::iUnknown* outer, COM::ClassID cid, COM::InterfaceID iid, void** result) = 0;
		};
	}
}
