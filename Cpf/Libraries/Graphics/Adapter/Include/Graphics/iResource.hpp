//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		struct iResource : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iResource"_crc64);

			virtual bool Map(void**, const Range* = nullptr) = 0;
			virtual void Unmap(const Range* range) = 0;
		};
	}
}
