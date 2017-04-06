//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;

		struct iClassInstance : COM::iUnknown
		{
			virtual COM::Result CPF_STDCALL CreateInstance(iRegistry*, COM::iUnknown*, COM::iUnknown**) = 0;
		};
	}
}
