//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
#include "Graphics/iOutput.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iAdapter : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iAdapter"_crc64);

			virtual const char* CPF_STDCALL GetDescription() const = 0;
			virtual size_t CPF_STDCALL GetVideoMemory() const = 0;
			virtual size_t CPF_STDCALL GetSystemMemory() const = 0;
			virtual size_t CPF_STDCALL GetSharedMemory() const = 0;
			virtual bool CPF_STDCALL IsSoftware() const = 0;
			virtual bool CPF_STDCALL IsRemote() const = 0;

			virtual GOM::Result CPF_STDCALL EnumerateOutputs(int32_t& count, iOutput**) const = 0;
		};
	}
}
