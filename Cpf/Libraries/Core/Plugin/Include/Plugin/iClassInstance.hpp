//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct CPF_EXPORT iClassInstance : COM::iUnknown
		{
			virtual COM::Result CPF_STDCALL CreateInstance(COM::iUnknown*, COM::iUnknown**) = 0;
		};
	}
}
