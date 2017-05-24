//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iBlob : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iBase"_crc64);

			virtual GOM::Result Initialize(const void*, int64_t) = 0;
			virtual void* CPF_STDCALL GetData() = 0;
			virtual int64_t CPF_STDCALL GetSize() = 0;
		};
	}
}
