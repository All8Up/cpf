//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include "COM/iUnknown.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iBlob : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iUnknown"_crc64);

			virtual COM::Result Initialize(const void*, int64_t) = 0;
			virtual void* CPF_STDCALL GetData() = 0;
			virtual int64_t CPF_STDCALL GetSize() = 0;
		};
	}
}
