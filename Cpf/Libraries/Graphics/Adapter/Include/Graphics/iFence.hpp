//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iFence : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iFence"_crc64);

			virtual uint64_t GetValue() const = 0;
			virtual void WaitFor(uint64_t value) = 0;
		};
	}
}
