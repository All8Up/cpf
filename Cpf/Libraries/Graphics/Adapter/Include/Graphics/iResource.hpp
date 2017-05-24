//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		struct iResource : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iResource"_crc64);

			virtual bool Map(void**, const Range* = nullptr) = 0;
			virtual void Unmap(const Range* range) = 0;
		};
	}
}
